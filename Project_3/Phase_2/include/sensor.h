// ===== GAZE BEHAVIOR MONITORING SYSTEM ===== //
// 
// File : sensor.h
// This module is used to generate the 
// gazepoints for the mobiles
//
// =========================================== // 
#ifndef __SENSOR_H__
#define __SENSOR_H__
#include "defs.h"

class sensor : public sc_module {
    public:
        // ----- PORTS ----- //
        sc_in_clk clk;
        sc_out <sc_uint<10> > gp_x;    // Gazepoint x
        sc_out <sc_uint<10> > gp_y;    // Gazepoint y
    
        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(sensor);
        sensor(sc_module_name name) :
        sc_module(name) {
            /* Generate gazepoint every clock cycle (100 HZ) */
            SC_CTHREAD(sensor_proc, clk);
            
            /* Output Ports Initialization */
            gp_x.initialize(0);
            gp_y.initialize(0);
        }
    private:
        // ----- METHODS ----- //
        void sensor_proc(void);
};

#endif // __SENSOR_H__
