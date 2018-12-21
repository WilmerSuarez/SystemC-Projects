//====== COUNTER ======//
//
// File : counter_2.h
//
//=====================//
#include "systemc.h"

SC_MODULE(counter_2) {
    // ----- PORTS ----- //
    sc_in <sc_uint<8> > in_2, in_3;
    sc_in <bool> clock, load_2, dec_2;
    sc_out <bool> overflow_2;
    sc_out <sc_uint<8> > count_2;

    // ----- INTERNAL VARIABLES ----- //
    sc_uint<8> count_prev_2, temp_2;
    
    // ----- METHODS ----- //
    void process_count_2();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(counter_2) {
        SC_METHOD(process_count_2);
            sensitive << clock.pos();
    }
};
