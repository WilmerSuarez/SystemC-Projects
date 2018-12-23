//============== MINI RISC PROCESSOR ============= //
//
// File : CTRL_driver.h
// Drives bits going into Control Module.
//
//================================================ //
#ifndef CTRL_DRIVER_H
#define CTRL_DRIVER_H
#include "systemc.h"

SC_MODULE(driver_CTRL) {
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_out<sc_bv<16> > driver_instruction, driver_pc_next_if, driver_rdest_data_in, driver_rsrc_data_in, driver_alu_result_exe, driver_data_dm;
    sc_out<sc_bv<4> > driver_flags;
    
    // ----- MEHODS ----- //
    void process_driver_CTRL();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(driver_CTRL) {
	    SC_CTHREAD(process_driver_CTRL, clk.pos());
    }
};

#endif // CTRL_DRIVER_H
