// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : mobile.h
// This module processes the gazepoint received by the sensor
// and transmits the processed packets the server
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
        sc_in<sc_uint<10> > gp_x;   // Gazepoint Image coordinate x, from sensor
        sc_in<sc_uint<10> > gp_y;   // Gazepoint Image coordinate y, from sensor
        sc_in<bool> busy;           //
        sc_in<bool> response;       // Response from server on network availability 
        sc_out<bool> request;       // Network request signal - sent to server
        sc_out<sc_bv<3> > status;   // Status values - sent to server
        /* Status Bit Information
            Bit 0: Request to Send Data?
            Bit 1: Sending Data
            Bit 2: Finished Sending Data
        */

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(mobile);
        mobile(sc_module_name name) : 
        sc_module(name) {
            SC_THREAD(mobile_converter_proc);
                sensitive << gp_x << gp_y;    
            
            SC_THREAD(mobile_compression_proc);
                sensitive << _compress_e;

            SC_THREAD(mobile_packetizer_proc);
                sensitive << _packetize_e;

            SC_THREAD(mobile_tx_proc);
                sensitive << _tx_e;
                    
            /* Output Ports Initialization */
            status.initialize(0);

            /* Variable Initialization */
            tuple_count = 0;
            tx_packet_count = 0;
        }
    private:
        // ----- METHODS ----- //
        void mobile_converter_proc();
        void mobile_compression_proc();
        void mobile_packetizer_proc();
        void mobile_tx_proc();
        
        // ----- INTERNAL VARIABLES/SIGNALS ----- //
        // ===== CONVERTER ===== //
        /* ROI (Region of Interest) information */
        const std::vector<std::vector<std::pair<uint, uint> > > _roi = { 
            { {50, 20},   {400, 320} },
            { {50, 370},  {450, 1000} },
            { {470, 20},  {600, 900} },
            { {670, 40},  {950, 550} },
            { {680, 700}, {1000, 1000} } 
        };
        /* Store ROI indices with the current time */
        std::map<sc_time, uint> roi_time_map;
        /* Triggered when gazepoints are processed (ready to compress) */
        sc_event _compress_e; 
        
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
