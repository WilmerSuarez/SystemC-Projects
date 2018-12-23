//============ MINI RISC PROCESSOR =========== //
//
// File : DM_monitor.h
// Monitor Data Memory inputs and outputs.
//
//============================================ //
#ifndef DM_MONITOR_H
#define DM_MONITOR_H
#include "systemc.h"

SC_MODULE(monitor_DM) {
    // ----- PORTS ----- //
    sc_in<bool> monitor_CTRL_DM_RW;
    sc_in<sc_bv<2> > monitor_CTRL_RESULT_SELECT;
    sc_in<sc_bv<16> > monitor_dm_addr, monitor_alu_result, monitor_pc_next, monitor_data_in, monitor_dm_result, monitor_data_out, monitor_final_result;

    // ----- MEHODS ----- //
    void process_monitor_DM();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(monitor_DM) {
	    SC_METHOD(process_monitor_DM);
            dont_initialize();
	        sensitive << monitor_CTRL_DM_RW << monitor_CTRL_RESULT_SELECT << monitor_dm_addr << monitor_alu_result << monitor_pc_next << monitor_data_in << monitor_dm_result << monitor_data_out << monitor_final_result;
    }
};

#endif // DM_MONITOR_H
