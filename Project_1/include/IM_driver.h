//============== MINI RISC PROCESSOR ============= //
//
// File : IM_driver.h
// Drives bits going into the Instruction Memory.
//
//================================================ //
#ifndef IM_DRIVER_H
#define IM_DRIVER_H
#include "systemc.h"

SC_MODULE(driver_IM) {
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_out<sc_bv<2> > driver_CTRL_PC_SRC;
    sc_out<sc_bv<16> > driver_branch_disp, driver_jmp_target;
    
    // ----- MEHODS ----- //
    void process_driver_IM();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(driver_IM) {
	    SC_CTHREAD(process_driver_IM, clk.pos());
    }
};

#endif // IM_DRIVER_H
