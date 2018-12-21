// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : server.h
// This module controls the network usage and processes the 
// data received from the mobiles
// Also sends the images to be analyzed to the mobiles at 
// specific times 
//
// ============================================================= //
#include <random>
#include <chrono>
#include "server.h"

/*
    Handles the requests from the passed in mobile
*/
void server::handle_request(uint m) {
    cout << "MOBILE_" << m+1 << endl;
    /* Allow mobile m to use Network */
    if(!(busy.read()) && ((status[m].read() & REQUEST) == REQUEST)) {
        response[m].write(1);
        /* 
           Deny use of Network for other mobiles if they requested 
           access simultaneously 
        */
        for(uint i = 0; i < MOBILE_NUM; ++i) {
            if(!(response[i] == response[m])) {
                response[i].write(0);
            }
        }
        /* Wait for mobile to cease request */
        wait(request[m]->negedge_event());
        /* Network is no busy with current mobile */
        busy.write(1);
        /* Wait for mobile to update its status */
        wait(status[m]->value_changed_event());
        if((status[m].read() & SENDING) == SENDING) { 
            /* Wait for Transmition to finish */
            wait(status[m]->value_changed_event());
            if((status[m].read() & DONE) == DONE) {
                /* Network is now free */
                busy.write(0);
            }
        }
    }
    /* Reset Server Response */
    response[m].write(0);
}

/*
    Receives requests from mobiles to process their packets
*/
void server::server_rx_proc() {
    while(true) {
        /* Wait for Requests From Mobiles */
        wait(request[0]->posedge_event() | 
        request[1]->posedge_event() | 
        request[2]->posedge_event() | 
        request[3]->posedge_event()); 

        cout << "@: " << sc_time_stamp() << " : In RX: Server: ";
        /* Check which mobile triggered the process */
        for(uint i = 0; i < MOBILE_NUM; ++i) {
            if(request[i].read()) {
                handle_request(i);
                break;
            }
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
    Transfers Image Packets to the Mobiles at 
    specific predetermined times
*/
void server::server_tx_proc() {
    while(true) {
        wait(tx_e.posedge_event());
        /* Transfer Image Packets to all Mobiles */
        if(!busy.read()) {
            cout << "Starting Image TX: @: " << sc_time_stamp() << endl;
            busy.write(1);
            for(uint i = 0; i < MOBILE_NUM; ++i) {
                for(uint j = 0; j < _max_p_count; ++j) {
                    /* Wait for first Image Packet to transmit */
                    wait((_packet_size/(double)_bw), SC_MS);
                    /* Notify Mobile of new packet */
                    img_packet[i].write(1);
                    /* Wait Delta */
                    busy.write(0);
                    wait(random_time(_packet_transmit_time), SC_MS);
                    busy.write(1);
                    img_packet[i].write(0);
                }
            }
            
        } else {
            /* Wait Random Time for Network to be Available */
            wait(random_time(_packet_transmit_time), SC_MS);
        }
        busy.write(0);
    }
}
