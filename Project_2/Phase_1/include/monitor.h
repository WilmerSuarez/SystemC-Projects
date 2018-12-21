// ============== ROBOT NAVIGATION ============== //
// 
// File : monitor.h
// This module monitors the inputs and outputs of 
// the Robot Navigation System.
//
// ============================================== //
#ifndef __MONITOR_H__
#define __MONITOR_H__
#include "systemc.h"

SC_MODULE(monitor) {
    // ----- PORTS ----- //
    sc_in<bool> monitor_packet_validS, monitor_packet_validE;
    sc_in<sc_bv<3> > monitor_packet_fromE, monitor_packet_fromS, monitor_packet_toE, monitor_packet_toS;

    // ----- MEHODS ----- //
    void monitor_proc();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(monitor) {
	    SC_METHOD(monitor_proc);
            dont_initialize();
	        sensitive << monitor_packet_validS << monitor_packet_validE << monitor_packet_fromE << monitor_packet_fromS << monitor_packet_toE << monitor_packet_toS;
    }
};

#endif // __MONITOR_H__
