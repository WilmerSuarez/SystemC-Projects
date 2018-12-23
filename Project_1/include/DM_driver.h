//============ MINI RISC PROCESSOR =========== //
//
// File : DM_driver.h
// Drives bits going into the Data Memory.
//
//============================================ //
#ifndef DM_DRIVER_H
#define DM_DRIVER_H
#include "systemc.h"

SC_MODULE(driver_DM) {
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_out<bool> driver_CTRL_DM_RW;
    sc_out<sc_bv<2> > driver_CTRL_RESULT_SELECT;
    sc_out<sc_bv<16> > driver_dm_addr, driver_alu_result, driver_pc_next, driver_data_in, driver_dm_result;
   
    // ----- MEHODS ----- //
    void process_driver_DM();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(driver_DM) {
	    SC_CTHREAD(process_driver_DM, clk.pos());
    }
};

#endif // DM_DRIVER_H
