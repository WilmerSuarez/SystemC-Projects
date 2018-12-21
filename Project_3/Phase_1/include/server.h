// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : server.h
// This module controls the network usage and processes the 
// data received from the mobiles
//
// ============================================================= //
#ifndef __SERVER_H__
#define __SERVER_H__
#include "defs.h"

class server : public sc_module {
    public:
        // ----- PORTS ----- //
        sc_in<bool> m1_request{"M1_REQUEST"};     // Request from mobile_1 to use network and transmit data
        sc_in<bool> m2_request{"M2_REQUEST"};     // Request from mobile_2 to use network and transmit data
        sc_in<sc_bv<3> > m1_status{"M1_STATUS"};  // Status values from mobile_1
        sc_in<sc_bv<3> > m2_status{"M2_STATUS"};  // Status values from mobile_2
        sc_out<bool> busy{"BUSY"};                // Network is busy flag
        sc_out<bool> response_1{"RESPONSE_1"};    // mobile_1 request response
        sc_out<bool> response_2{"RESPONSE_2"};    // mobile_2 request response

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(server);
        server(sc_module_name name) : 
        sc_module(name) {
            SC_THREAD(server_rx_proc);

            //SC_THREAD(server_tx_proc);
                //sensitive <<

            /* Output Ports Initialization */

            /* Variable/Signal Initialization */

        }
    private:
        // ----- METHODS ----- //
        void server_rx_proc();
        void server_tx_proc();

        // ----- INTERNAL VARIABLES/SIGNALS ----- //
        
};

#endif // __SERVER_H__
