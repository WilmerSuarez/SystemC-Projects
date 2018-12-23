// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : monitor.h
// This module 
//
// ============================================================= //
#ifndef __MONITOR_H__
#define __MONITOR_H__
#include "defs.h"

class monitor : public sc_module {
    public:
        // ----- PORTS ----- //
        sc_in_clk clk;
        
        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(monitor);
        monitor(sc_module_name name) : 
        sc_module(name) {
                
                    
            /* Output Ports Initialization */
            
        }
    private:
        // ----- METHODS ----- //
        
        // ----- INTERNAL VARIABLES & SIGNALS ----- //
       
};

#endif // __MONITOR_H__
