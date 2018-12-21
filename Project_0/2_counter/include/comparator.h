//====== COUNTER ======//
//
// File : comparator.h
//
//=====================//
#include "systemc.h"

SC_MODULE(comparator) {
    // ----- PORTS ----- //
    sc_in <sc_uint<8> > count_1, count_2;
    sc_in <bool> overflow_1, overflow_2;
    sc_out <bool> ended;

    // ----- METHODS ----- //
    void process_comparator();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(comparator) {
        SC_METHOD(process_comparator);
            sensitive << count_1 << count_2 << overflow_1 << overflow_2; 
    }
};
