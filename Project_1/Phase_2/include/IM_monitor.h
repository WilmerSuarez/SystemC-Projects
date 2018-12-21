//============== MINI RISC PROCESSOR ============= //
//
// File : IM_monitor.h
// Monitor Instruction Memory inputs and outputs.
//
//================================================ //
#ifndef IM_MONITOR_H
#define IM_MONITOR_H
#include "systemc.h"

SC_MODULE(monitor_IM) {
    // ----- PORTS ----- //
     sc_in<sc_bv<2> > monitor_CTRL_PC_SRC;
     sc_in<sc_bv<16> > monitor_branch_disp, monitor_jmp_target,
                   monitor_instruction, monitor_pc_next; 

    // ----- MEHODS ----- //
    void process_monitor_IM();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(monitor_IM) {
	    SC_METHOD(process_monitor_IM);
            dont_initialize();
	        sensitive << monitor_CTRL_PC_SRC << monitor_branch_disp << monitor_jmp_target << monitor_instruction << monitor_pc_next;
    }
};

#endif // IM_MONITOR_H
