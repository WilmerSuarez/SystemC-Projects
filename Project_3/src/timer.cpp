// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : timer.cpp
// This module processes the transfer-time-calcualtions for the
// images and triggeres the start of transmission to the mobiles
// from the server for each image.
//
// ============================================================= //
#include "timer.h"

/*
    Notifies Server when to begin
    transmitting each image.
*/
void timer::timer_proc() {
    /* Hold current time */
    sc_time c_time;
    while(true) {
        wait();
        c_time = sc_time_stamp(); // Get current simulation time

        /* Test against image start times */
        if((c_time == _start_times.front()) && !_start_times.empty()) {
            /* Notify Server of new image to transmit */ 
            tx_e.write(1);
            /* Next Image */  
            _start_times.erase(_start_times.begin());
        } else {
            tx_e.write(0);
        }
    }
}