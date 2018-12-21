//====== COUNTER ======//
//
// File : counter_1.h
//
//=====================//
#include "systemc.h"

SC_MODULE(counter_1) {
    // ----- PORTS ----- //
    sc_in <sc_uint<8> > in_1;
    sc_in <bool> clock, load_1, dec_1;
    sc_out <bool> overflow_1;
    sc_out <sc_uint<8> > count_1;

    // ----- INTERNAL VARIABLES ----- //
    sc_uint<8> count_prev_1, temp_1;

    // ----- METHODS ----- //
    void process_count_1();
    
    // ----- CONSTRUCTOR ----- //
    SC_CTOR(counter_1) {
        SC_METHOD(process_count_1);
	    sensitive << clock.pos();
    }
};
