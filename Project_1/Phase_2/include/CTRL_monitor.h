//============== MINI RISC PROCESSOR ============= //
//
// File : CTRL_monitor.h
// Monitors Control Module inputs and outputs.
//
//================================================ //
#ifndef CTRL_MONITOR_H
#define CTRL_MONITOR_H
#include "systemc.h"

SC_MODULE(monitor_CTRL) {
    // ----- PORTS ----- //
    sc_in<sc_bv<16> > monitor_instruction;          
    sc_in<sc_bv<16> > monitor_pc_next_if;           
    sc_in<sc_bv<4> > monitor_flags;                
    // RD Stage
    sc_in<sc_bv<4> > monitor_rdest_addr_rd;       
    sc_in<sc_bv<4> > monitor_rsrc_addr;            
    sc_in<sc_bv<16> > monitor_rdest_data_in;        
    sc_in<sc_bv<16> > monitor_rsrc_data_in;      
    // EXE Stage
    sc_in<bool> monitor_CTRL_ALU_REG_1;            
    sc_in<bool> monitor_CTRL_ALU_REG_2;          
    sc_in<sc_bv<5> > monitor_CTRL_ALU_OPCODE;     
    sc_in<sc_bv<2> > monitor_CTRL_PC_SRC;         
    sc_in<sc_bv<16> > monitor_jmp_tgt;             
    sc_in<sc_bv<16> > monitor_rsrc_data_out;      
    sc_in<sc_bv<16> > monitor_rdest_data_out;     
    sc_in<sc_bv<8> > monitor_immediate;           
    sc_in<sc_bv<16> > monitor_alu_result_exe;
    sc_in<sc_bv<16> > monitor_branch_disp;
    // MEM Stage
    sc_in<bool> monitor_CTRL_DM_RW;              
    sc_in<sc_bv<16> > monitor_alu_result_mem;     
    sc_in<sc_bv<16> > monitor_data_in;             
    sc_in<sc_bv<16> > monitor_data_dm;             
    // WB Stage
    sc_in<bool> monitor_CTRL_RF_WRITE;             
    sc_in<sc_bv<2> > monitor_CTRL_RESULT_SELECT;   
    sc_in<sc_bv<4> > monitor_rdest_addr_wb;        
    sc_in<sc_bv<16> > monitor_pc_next_wb;          
    sc_in<sc_bv<16> > monitor_alu_result_wb;       
    sc_in<sc_bv<16> > monitor_data_wb; 
    sc_in<sc_bv<16> > monitor_final_result;

    // ----- MEHODS ----- //
    void process_monitor_CTRL();

    // ----- CONSTRUCTOR ----- //
    SC_CTOR(monitor_CTRL) {
	    SC_METHOD(process_monitor_CTRL);
	        sensitive << monitor_instruction << monitor_pc_next_if;
            sensitive << monitor_flags << monitor_rdest_addr_rd;
            sensitive << monitor_rsrc_addr << monitor_rdest_data_in;
            sensitive << monitor_rsrc_data_in << monitor_CTRL_ALU_REG_1;
            sensitive << monitor_CTRL_ALU_REG_2 << monitor_CTRL_ALU_OPCODE;
            sensitive << monitor_CTRL_PC_SRC << monitor_jmp_tgt << monitor_rsrc_data_out; 
            sensitive << monitor_rdest_data_out << monitor_immediate;
            sensitive << monitor_alu_result_exe << monitor_CTRL_DM_RW;
            sensitive << monitor_alu_result_mem << monitor_data_in;
            sensitive << monitor_data_dm << monitor_CTRL_RF_WRITE; 
            sensitive << monitor_CTRL_RESULT_SELECT << monitor_rdest_addr_wb;
            sensitive << monitor_pc_next_wb << monitor_alu_result_wb << monitor_data_wb;
    }
};

#endif // CTRL_MONITOR_H
