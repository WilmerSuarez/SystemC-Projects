// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : sensor.h
// This module 
//
// ============================================================= //
#ifndef __SENSOR_H__
#define __SENSOR_H__
#include "defs.h"

class sensor : public sc_module {
    public:
        // ----- PORTS ----- //
    
        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(sensor);
        sensor(sc_module_name name) :
        sc_module(name) {

            /* Output Ports Initialization */

        }

    private:
        // ----- METHODS ----- //

        // ----- INTERNAL VARIABLES & SIGNALS ----- //
        
};

#endif // __SENSOR_H__
