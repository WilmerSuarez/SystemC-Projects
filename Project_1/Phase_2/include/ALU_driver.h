//============== MINI RISC PROCESSOR ============= //
//
// File : ALU_driver.h
// Drives bits going into the ALU.
//
//================================================ //
#ifndef ALU_DRIVER_H
#define ALU_DRIVER_H
#include "systemc.h"

SC_MODULE(driver_ALU) {
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_out<bool> driver_CTRL_ALU_REG_1, driver_CTRL_ALU_REG_2;
    sc_out<sc_bv<5> > driver_CTRL_ALU_OPCODE;
    sc_out<sc_bv<8> > driver_immediate_in;
    sc_out<sc_bv<16> > driver_rdest_data, driver_rsrc_data;
    
    // ----- MEHODS ----- //
    void process_driver_ALU();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(driver_ALU) {
	    SC_CTHREAD(process_driver_ALU, clk.pos());
    }
};

#endif // ALU_DRIVER_H
