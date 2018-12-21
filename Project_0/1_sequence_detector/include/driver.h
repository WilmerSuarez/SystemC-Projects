//============== SEQUENCE DETECTOR =============
//
// File : driver.h
// Drives bits going into the sequence detector
//
//==============================================
#include "systemc.h"

SC_MODULE(driver) {
    // ----- PORTS ----- //
    sc_out <bool> driver_reset, driver_clear, driver_input; 
    
    // ----- MEHODS ----- //
    void process_driver();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(driver) {
	    SC_THREAD (process_driver);
    }
};
