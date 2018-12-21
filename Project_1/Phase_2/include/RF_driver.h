//============ MINI RISC PROCESSOR =========== //
//
// File : RF_driver.h
// Drives bits going into the Register File.
//
//============================================ //
#ifndef RF_DRIVER_H
#define RF_DRIVER_H
#include "systemc.h"

SC_MODULE(driver_RF) {
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_out<bool> driver_CTRL_RF_WRITE;
    sc_out<sc_bv<4> > driver_rdest_addr, driver_rsrc_addr, driver_wb_reg;
    sc_out<sc_bv<16> > driver_data_in;
    
    // ----- MEHODS ----- //
    void process_driver_RF();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(driver_RF) {
	    SC_CTHREAD(process_driver_RF, clk.pos());
    }
};

#endif // RF_DRIVER_H
