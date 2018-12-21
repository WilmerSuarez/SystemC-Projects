//============== MINI RISC PROCESSOR ============= //
//
// File : ALU_monitor.h
// Monitor ALU inputs and outputs.
//
//================================================ //
#ifndef ALU_MONITOR_H
#define ALU_MONITOR_H
#include "systemc.h"

SC_MODULE(monitor_ALU) {
    // ----- PORTS ----- //
    sc_in<bool>  monitor_CTRL_ALU_REG_1,  monitor_CTRL_ALU_REG_2;
    sc_in<sc_bv<4> > monitor_flags;
    sc_in<sc_bv<5> > monitor_CTRL_ALU_OPCODE;
    sc_in<sc_bv<8> > monitor_immediate_in;
    sc_in<sc_bv<16> > monitor_rdest_data, monitor_rsrc_data, monitor_immediate_out, monitor_alu_result;

    // ----- MEHODS ----- //
    void process_monitor_ALU();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(monitor_ALU) {
	    SC_METHOD(process_monitor_ALU);
            dont_initialize();
	        sensitive << monitor_CTRL_ALU_REG_1 << monitor_CTRL_ALU_REG_2 << monitor_flags << monitor_CTRL_ALU_OPCODE << monitor_immediate_in;
            sensitive << monitor_rdest_data << monitor_rsrc_data << monitor_immediate_out << monitor_alu_result;
    }
};

#endif // ALU_MONITOR_H
