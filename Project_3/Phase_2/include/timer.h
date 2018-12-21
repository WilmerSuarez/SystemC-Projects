// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : timer.h
// This module processes the transfer-time-calcualtions for the
// images and triggeres the start of transmission to the mobiles
// from the server for each image.
//
// ============================================================= //
#ifndef __TIMER_H__
#define __TIMER_H__
#include "defs.h"

class timer : public sc_module {
    public:
        // ----- PORTS ----- //
        sc_in_clk clk;
        sc_out<bool> tx_e;

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(timer);
        timer(sc_module_name name, std::vector<sc_time> start_times) : 
        _start_times(start_times),
        sc_module(name) {
            SC_CTHREAD(timer_proc, clk);
        }
    private:
        // ----- METHODS ----- //
        void timer_proc();
        
        // ----- INTERNAL VARIABLES/SIGNALS ----- //
        /* Vector of all the image start times */
        std::vector<sc_time> _start_times;
};

#endif // __TIMER_H__
