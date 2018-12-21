// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : sensor_driver.h
// This module 
//
// ============================================================= //
#ifndef __MOBILE_DRIVER_H__
#define __MOBILE_DRIVER_H__
#include "defs.h"

SC_MODULE(mobile_driver) {
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_out <sc_bv<3> > driver_packet_fromE{"DRIVER_PACKET_FROME"};        // Packet from Environment
    
    // ----- MEHODS ----- //
    void mobile_driver_proc();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(mobile_driver) {
	    
    }
};

#endif // __MOBILE_DRIVER_H__
