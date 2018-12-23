// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : server.h
// This module controls the network usage and processes the 
// data received from the mobiles
// Also sends the images to be analyzed to the mobiles at 
// specific time intervals
//
// ============================================================= //
#ifndef __SERVER_H__
#define __SERVER_H__
#include "defs.h"
#include "timer.h"

class server : public sc_module {
    public:
        // ----- PORTS ----- //
        sc_in_clk clk;
        sc_in<bool> request[MOBILE_NUM];      // Request from mobiles to use network and transmit data
        sc_in<sc_bv<3> > status[MOBILE_NUM];  // Status values from mobiles
        sc_out<bool> response[MOBILE_NUM];    // mobiles request response
        sc_out<bool> busy;                    // Network is busy flag
        sc_out<bool> img_packet[MOBILE_NUM];  // Signaling the end of an image packet 

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(server);
        server(sc_module_name name, std::vector<sc_time> start_times, const double packet_transmit_time, const uint max_p_count, const uint packet_size, const uint bw) : 
        _timer("TIMER", start_times),
        _packet_transmit_time(packet_transmit_time), 
        _max_p_count(max_p_count),
        _packet_size(packet_size),
        _bw(bw),
        sc_module(name) {
            SC_THREAD(server_rx_proc);

            SC_THREAD(server_tx_proc);

            /* Connect Timer */
            _timer(clk, tx_e);
        }
    private:
        // ----- METHODS ----- //
        void server_rx_proc();
        void server_tx_proc();
        void handle_request(uint);

        /* Timer Instance */
        timer _timer;

        // ----- INTERNAL VARIABLES/SIGNALS ----- //
        sc_signal<bool> tx_e;  // Triggered when it's time to transmit new image to mobiles 
        const double _packet_transmit_time;
        /* Total number of Image Packets */
        const uint _max_p_count;
        const uint _packet_size;    // Size of server to mobile packet
        const uint _bw;             // Bandwidth size 
};

#endif // __SERVER_H__
