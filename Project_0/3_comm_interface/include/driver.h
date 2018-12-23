//=== COMMUNICATION INTERFACE ===//
//
// File : driver.h
//
//===============================//
#include "systemc.h"

SC_MODULE(driver) {
    // ===== PORTS ===== //
    sc_out <bool> driver_reset, driver_clear;
    sc_out <sc_uint<12> > driver_in_data;

    // ===== METHODS ===== //
    void process_driver();
    
    // ===== CONSTRUCTOR ===== //
    SC_CTOR(driver) {
	    SC_THREAD(process_driver);	    
    }
};
