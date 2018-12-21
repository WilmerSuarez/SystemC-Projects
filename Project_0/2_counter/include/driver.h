//====== COUNTER ======//
//
// File : driver.h
//
//=====================//
#include "systemc.h"

SC_MODULE(driver) {
    // ----- PORTS ----- //
    sc_out <sc_uint<8> > in_1, in_2, in_3;
    sc_out <bool> load_1, load_2, dec_1, dec_2; 

    // ----- METHODS ----- //
    void process_driver();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(driver) {
        SC_THREAD (process_driver);
    }
};
