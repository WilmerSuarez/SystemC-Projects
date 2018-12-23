// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : sensor_driver.h
// This module 
//
// ============================================================= //
#ifndef __SENSOR_DRIVER_H__
#define __SENSOR_DRIVER_H__
#include "defs.h"

SC_MODULE(sensor_driver) {
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_out <sc_bv<3> > driver_packet_fromE{"DRIVER_PACKET_FROME"};        // Packet from Environment
    
    // ----- MEHODS ----- //
    void sensor_driver_proc();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(sensor_driver) {
	    
    }
};

#endif // __SENSOR_DRIVER_H__
