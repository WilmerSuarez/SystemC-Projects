// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : mobile.cpp
// This module processes the gazepoint received by the sensor
// and transmits the processed packets the server
//
// ============================================================= //
#include <random>
#include <chrono>
#include "mobile.h"

/*
    Converts gazepoint coordinates to ROI indices
*/
void mobile::mobile_converter_proc() {
    wait(_img_e); /* Wait for first image to arrive */
    while(true) {
        wait(gp_x.value_changed_event() | gp_y.value_changed_event());
        /* Wait for first image to arrive */
        for(uint r = 0; r < ROI_NUM; ++r) {
            /* Test if gazepoint is within current Image ROI */
            if((gp_x.read() >= _roi[img][r][0].first && 
                gp_x.read() <= _roi[img][r][1].first) && 
                (gp_y.read() >= _roi[img][r][0].second && 
                gp_y.read() <= _roi[img][r][1].second)) {
                /* Set ROI index and the current time */
                roi_time_map.insert(std::pair<sc_time, uint>(sc_time_stamp(), r+1));
                break;
            }
        }
        /* Notify Compressor of new ROI index */
        _compress_e.notify();
    }
}

/*
    Compress the ROI index into tuples 
    Tuple: [iroi, t1, t2]
*/
void mobile::mobile_compression_proc() {
    sc_time itime(10, SC_MS);
    uint roi;
    sc_time t;
    const char* _name = sc_core::sc_get_current_process_b()->get_parent_object()->basename();
    while(true) {
        wait();
       // cout << "@: " << sc_time_stamp() << " : In Compressor: mobile: " << _name << endl;
        /* No compression if gazepoint is not within any ROI */
        if(!roi_time_map.empty()) {
            t = roi_time_map.begin()->first;    // Time period of current ROI index
            roi = roi_time_map.begin()->second; // Current ROI index
            /* Test if ROI index is still the same */
            if(!_tTable.empty() && (roi == _tTable.back().iroi) && !(t > _tTable.back().t2)) {
                _tTable.back().t2 = t+itime;
            } else {
                /* Create tuple */
                _tup = { roi, t, t+itime };
                /* Notify Packetsizer of new Tuple */
                _packetize_e.notify();
            }  
            /* Remove old roi/time data */
            roi_time_map.erase(roi_time_map.begin());
        }
    }
}

/*
    Creates a packet of tuples to transmit to server
    Packets contain 20 tuples
*/
void mobile::mobile_packetizer_proc() {
    const char* _name = sc_core::sc_get_current_process_b()->get_parent_object()->basename();
    while(true) {
        wait();
        //cout << "@: " << sc_time_stamp() << " : In Packetizer: mobile: " << _name << endl;
        /* Insert tuple into tuple table */
        _tTable.push_back(_tup);
        /* Increment tuple count */
        ++tuple_count;
        if(tuple_count == PACKET_SIZE) {
            /* Increment packet count and reset tuple count & tuple list */
            ++tx_packet_count;
            cout << "Packet count: " << tx_packet_count << " " << _name << endl;
            tuple_count = 0;
            _tTable.clear();
            /* Notify TX of New Packet */
            _tx_e.notify();
        }
    }
}

/* 
    Generate a random time to wait for the network to 
    be available
    Time Range: [0, PACKET_TRANSMIT_TIME]
*/
static double random_time(double _packet_transmit_time) {
    /* Generate unique seed */
    uint seed = std::chrono::steady_clock::now().time_since_epoch().count();
    /* Create default random engine using the seed */
    std::default_random_engine r(seed);
    /* Distribute the (real) random number. Range: [(PACKET_TRANSMIT_TIME/2), PACKET_TRANSMIT_TIME] */
    std::uniform_real_distribution<double> d((_packet_transmit_time/2), _packet_transmit_time);
    return d(r);
}

/*
    Transmit Packets to the Server
*/
void mobile::mobile_tx_proc() {
    /* Get name of current Mobile */
    const char* _name = sc_core::sc_get_current_process_b()->get_parent_object()->basename();
    while(true) {
        /* If packet buffer is empty */
        if(!tx_packet_count) {
            wait();
        }
        //cout << "@: " << sc_time_stamp() << " : In TX: mobile: " << _name << endl;
        if(busy.read()) {
            /* Wait Random Time */
            wait(random_time(_packet_transmit_time), SC_MS);
        } else {
            /* Status: Can I Send Data? */                           
            status.write(REQUEST);                                     
            /* Send Network Use Request */
            request.write(1);
            /* Wait for Server respond to request - Timeout 10ms */
            wait(10, SC_MS, response->posedge_event());
            request.write(0);
            /* If response is No */
            if(!response.read()) {
                /* Wait Random Time */
                wait(random_time(_packet_transmit_time), SC_MS);
            /* If response is Yes */
            } else {
                /* Wait for the busy signal to be set */
                wait(busy->posedge_event());
                /* Status: Sending Data */  
                status.write(SENDING);
                /* Wait for Packet to Transmit */
                wait(_packet_transmit_time, SC_SEC); 
                /* Status: Finished Sending Data */
                status.write(DONE);
                /* Decrement Packet Count */
                --tx_packet_count;
                cout << "@: " << sc_time_stamp() << " : " << _name << ": Tranmission complete" << endl;
            }
        }   
    }
}

/*
    Receive Image Packets fromt the Server
*/
void mobile::mobile_rx_proc() {
    while(true) {
        wait(img_packet.posedge_event());
        ++rx_img_packet;
        //cout << "Mobile: RX : img_packet: " << rx_img_packet << endl;
        if(rx_img_packet == _max_img_packet_count) {
            cout << "IMAGE: @: " << sc_time_stamp() << endl;
            /* Full image received */
            ++img;
            /* Reset image packet count */
            rx_img_packet = 0;
            /* Notify Converter of New Image */
            if(!img)
                _img_e.notify();
        }
    }
}
