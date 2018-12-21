//============ MINI RISC PROCESSOR =========== //
//
// File : RF_monitor.h
// Monitor Register File inputs and outputs.
//
//============================================ //
#ifndef RF_MONITOR_H
#define RF_MONITOR_H
#include "systemc.h"

SC_MODULE(monitor_RF) {
    // ----- PORTS ----- //
    sc_in<bool> monitor_CTRL_RF_WRITE;
    sc_in<sc_bv<4> > monitor_rdest_addr, monitor_rsrc_addr, monitor_wb_reg;
    sc_in<sc_bv<16> > monitor_data_in, monitor_rdest_data, monitor_rsrc_data; 

    // ----- MEHODS ----- //
    void process_monitor_RF();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(monitor_RF) {
	    SC_METHOD(process_monitor_RF);
            dont_initialize();
	        sensitive << monitor_CTRL_RF_WRITE << monitor_rdest_addr << monitor_rsrc_addr << monitor_wb_reg << monitor_data_in << monitor_rdest_data << monitor_rsrc_data;
    }
};

#endif // RF_MONITOR_H
