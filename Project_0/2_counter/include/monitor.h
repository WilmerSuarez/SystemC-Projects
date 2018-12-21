//====== COUNTER ======//
//
// File : monitor.h
//
//=====================//
#include "systemc.h"

SC_MODULE(monitor) {
    // ----- PORTS ----- //
    sc_in <sc_uint<8> > monitor_in_1, monitor_in_2, monitor_in_3, monitor_count_1, monitor_count_2;
    sc_in <bool> monitor_load_1, monitor_load_2, monitor_dec_1, monitor_dec_2, monitor_overflow_1, monitor_overflow_2, monitor_ended;

    // ----- METHODS ----- //
    void process_monitor();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(monitor) {
        SC_METHOD (process_monitor);
	    sensitive << monitor_in_1 << monitor_in_2 << monitor_in_3 << monitor_load_1 << monitor_load_2 << monitor_dec_1 << monitor_dec_2 << monitor_overflow_1 << monitor_overflow_2 << monitor_count_1 << monitor_count_2 << monitor_ended;
    }
};  
