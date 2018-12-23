// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : mobile.h
// This module processes the gazepoint coordinates received by 
// the sensor and transmits the processed packets the server
// It provides different ROIs to analyze once the "image" is 
// received from the server
//
// ============================================================= //
#ifndef __MOBILE_H__
#define __MOBILE_H__
#include <map>
#include <vector>
#include "sensor.h"
#include "defs.h"

class mobile : public sc_module {
    public:
        // ----- PORTS ----- //
        sc_in_clk clk;
        sc_in<bool> busy;           // Network Busy Flag
        sc_in<bool> response;       // Response from server on network availability 
        sc_in<bool> img_packet;     // Image transmission complete
        sc_out<bool> request;       // Network request signal - sent to server
        sc_out<sc_bv<3> > status;   // Status values - sent to server
        /* 
            Status Bit Information
                Bit 0: Request to Send Data
                Bit 1: Sending Data
                Bit 2: Finished Sending Data
        */

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(mobile);
        mobile(sc_module_name name, const uint max_img_packet_count, const double packet_transmit_time) : 
        sc_module(name),
        _max_img_packet_count(max_img_packet_count),
        _packet_transmit_time(packet_transmit_time),
        _sensor("SENSOR") {
            SC_THREAD(mobile_converter_proc);
            
            SC_THREAD(mobile_compression_proc);
                sensitive << _compress_e;

            SC_THREAD(mobile_packetizer_proc);
                sensitive << _packetize_e;

            SC_THREAD(mobile_tx_proc);
                sensitive << _tx_e;

            SC_THREAD(mobile_rx_proc);

            /* Connect Sensor */
            _sensor(clk, gp_x, gp_y);
                    
            /* Output Ports Initialization */
            status.initialize(0);

            /* Variable Initialization */
            tuple_count = 0;
            tx_packet_count = 0;
            rx_img_packet = 0;
            img = -1;
        }
    private:
        // ----- METHODS ----- //
        void mobile_converter_proc();
        void mobile_compression_proc();
        void mobile_packetizer_proc();
        void mobile_tx_proc();
        void mobile_rx_proc();

        /* Sensor Instance */
        sensor _sensor;
        
        // ----- INTERNAL VARIABLES/SIGNALS ----- //
        /* Max Image Packet Count */
        const uint _max_img_packet_count;
        /* Amount of time for completion of Packet Transmition (Mobile -> Server) */
        const double _packet_transmit_time;

        // ===== SENSOR SIGNALS ===== //
        sc_signal<sc_uint<10> > gp_x;   // Gazepoint Image coordinate x, from sensor
        sc_signal<sc_uint<10> > gp_y;   // Gazepoint Image coordinate y, from sensor

        // ===== CONVERTER ===== //
        /* ROI (Region of Interest) information */
        const std::vector<ROI> _roi = {
            /* Image 1 ROIs */
            { { {50, 20}, {400, 320} }, { {50, 370}, {450, 1000} }, { {470, 20}, {600, 900} }, { {670, 40}, {950, 550} }, { {680, 700}, {1000, 1000} },},
            /* Image 2 ROIs */
            { { {50, 140}, {650, 320} }, { {50, 590}, {1000, 1000} }, { {50, 20}, {600, 100} }, { {50, 350}, {950, 550} }, { {680, 20}, {1000, 300} },},
            /* Image 3 ROIs */
            { { {50, 20}, {400, 320} }, { {50, 370}, {450, 1000} }, { {470, 20}, {600, 900} }, { {670, 40}, {950, 550} }, { {680, 700}, {1000, 1000} },},
            /* Image 4 ROIs */
            { { {360, 360}, {450, 540} }, { {50, 590}, {1000, 1000} }, { {635, 325}, {750, 500} }, { {50, 350}, {122, 550} }, { {50, 20}, {1000, 300} },},
            /* Image 5 ROIs */
            { { {360, 820}, {450, 980} }, { {50, 590}, {140, 1000} }, { {360, 500}, {480, 730} }, { {180, 655}, {265, 890} }, { {560, 300}, {760, 990} },},
        };
        /* Store ROI indices with the current time */
        std::map<sc_time, uint> roi_time_map;
        /* Triggered when gazepoints are processed (ready to compress) */
        sc_event _compress_e; 
        /* Image and Image Packet counters */
        uint rx_img_packet;
        uint img;
        /* Triggered when new Image is to be displayed */
        sc_event _img_e;
        
        // ===== COMPRESSION ===== // 
        /* Tuple */
        struct _tuple {
            uint iroi;      // ROI index
            sc_time t1;     // Start time
            sc_time t2;     // End time
        } _tup;
        /* Triggered when new tuple created */ 
        sc_event _packetize_e; 

        // ===== PACKETIZER ===== //
        /* Tuple Table */
        std::vector<_tuple> _tTable;
        uint tuple_count;       // Current number of tuples inside the Tuple List (Packet = 20 tuples)
        uint tx_packet_count;   // Current number of packets to transfer to server 

        // ===== TX ===== //
        /* Triggered when packet count is incremented */ 
        sc_event _tx_e;
};

#endif // __MOBILE_H__
