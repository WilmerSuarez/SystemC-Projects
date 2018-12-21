//============== SEQUENCE DETECTOR ==============
//
// File : monitor.h
// Monitor sequence detector outputs and inputs
//
//===============================================
#include "systemc.h"

SC_MODULE(monitor) {
    // ----- PORTS ----- //
    sc_in <bool> monitor_reset, monitor_clear, monitor_input, monitor_output;

    // ----- METHODS ----- //
    void process_monitor();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(monitor) {
	    SC_METHOD(process_monitor);
	        sensitive << monitor_reset << monitor_clear << monitor_input << monitor_output;
    }
};
