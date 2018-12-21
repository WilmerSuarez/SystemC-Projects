//=== COMMUNICATION INTERFACE ===//
//
// File : monitor.h
//
//===============================//
#include "systemc.h"

SC_MODULE(monitor) {
    // ===== PORTS ===== //
    sc_in <bool> monitor_reset, monitor_clear;
    sc_in <sc_uint<12> > monitor_in_data;
    sc_in <sc_uint<8> > monitor_count, monitor_error;
    sc_in <sc_uint<4> > monitor_payload;

    // ===== METHODS ===== //
    void process_monitor();

    // ===== CONSTRUCTOR ===== //
    SC_CTOR(monitor) {
        SC_METHOD(process_monitor);
	    sensitive << monitor_reset << monitor_clear << monitor_in_data << monitor_count << monitor_error << monitor_payload;
    }
};
