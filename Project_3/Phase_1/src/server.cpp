// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : server.cpp
// This module controls the network usage and processes the 
// data received from the mobiles
//
// ============================================================= //
#include "server.h"

/*
    Receives requests from mobiles to process their packets
*/
void server::server_rx_proc() {
    while(true) {
        /* Wait for Requests From Mobiles */
        wait(m1_request->posedge_event() | m2_request->posedge_event()); 

        cout << "@: " << sc_time_stamp() << " : In RX: Server: ";
        /* Check which mobile triggered the process */
        if(m1_request.read()) {
            cout << "MOBILE_1" << endl;
            /* Allow mobile 1 to use Network */
            if(!(busy.read()) && ((m1_status.read() & REQUEST) == REQUEST)) {
                response_1.write(1);
                wait(m1_request->negedge_event());
                busy.write(1);
                wait(m1_status->value_changed_event());
                if((m1_status.read() & SENDING) == SENDING) { 
                    /* Wait for Transmition to finish */
                    wait(m1_status->value_changed_event());
                    if((m1_status.read() & DONE) == DONE) {
                        busy.write(0);
                    }
                }
            }
            /* Rest Response */
            response_1.write(0);
        } else if(m2_request.read()) {
            cout << "MOBILE_2" << endl;
            if(!(busy.read()) && ((m2_status.read() & REQUEST) == REQUEST)) {
                response_2.write(1);
                wait(m2_request->negedge_event());
                busy.write(1);
                wait(m2_status->value_changed_event());
                if((m2_status.read() & SENDING) == SENDING) { 
                    /* Wait for Transmition to finish */
                    wait(m2_status->value_changed_event());
                    if((m2_status.read() & DONE) == DONE) {
                        busy.write(0);
                    }
                }
            }
            /* Rest Response */
            response_2.write(0);
        }
    }
}
