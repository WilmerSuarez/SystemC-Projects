//============== MINI RISC PROCESSOR ==============
//
// File : main.cpp
// 
//===============================================
#include "IM.cpp"
#include "RF.cpp"
#include "DM.cpp"
#include "ALU.h"
#include "CTRL.h"
#include "CTRL_monitor.h"
#include "systemc.h"

int sc_main(int argc, char* argv[]) {
    // ----- CLOCK ----- //
    sc_clock tb_clock ("tb_clock", 1, SC_NS, false);

    // ============= INSTRUCTION MEMORY ============= //
    const sc_bv<16> im_instr[100] = {
        0x0000, // NOP
        0x0000, // NOP
        0x0000, // NOP
        0x0000, // NOP
        0x0000, // NOP
        0x0050, // ADD
        0x5044, // ADDI
        0x0094, // SUB
        0x9003, // SUBI 
        0xB202,  // CMPI 
        0x0014, // AND
        0x1020, // ANDI
        0x0025, // OR
        0x2090, // ORI
        0x0039, // XOR
        0x3084, // XORI
        0x00D6, // MOV
        0xD089, // MOVI
        0x8042, // LSH
        0x8013, // LSHI
        0x8061, // ASH
        0x8034, // ASHI
        0xF083, // LUI
        0x4902, // LOAD
        0x4043, // STOP
        0x0000, // NOP
        0xC0E9, // BCOND
        0x0000, // NOP
        0x0000, // NOP
        0xD202,  // CMPI
        0x0000, // NOP
        0x40CB, // JCOND
        0x0000, // NOP
        0x0000, // NOP
        0x0000, // NOP
        0x4086, // JAL
        0x0000, // NOP
        0x0000, // NOP
        0x0000  // NOP
    }; // Array of instructions
    const size_t im_instr_size = sizeof(im_instr) / sizeof(im_instr[0]); // Size of array ^

    // ============= REGISTER FILE ============= //
    const sc_bv<16> rf_data[16] = {
        0xDEAD, 
        0x1111,
        0x0002,
        0x3333,
        0x4444,
        0x5555, 
        0x0005,
        0x7777,
        0x1234,
        0x5678,
        0x1467, 
        0x0024,
        0x3456,
        0x7432,
        0x5435,
        0x3214
    }; // Array of data
    const size_t rf_data_size = sizeof(rf_data) / sizeof(rf_data[0]); // Size of array ^

   // ============= DATA MEMORY ============= //
    const sc_bv<16> dm_data[16] = {
        0x0AA0, 
        0x0A01,
        0x0222,
        0x0333,
        0x0444,
        0x0555, 
        0x0666,
        0x0777,
        0x0234,
        0x0678,
        0x3214
    }; // Array of data
    const size_t dm_data_size = sizeof(dm_data) / sizeof(dm_data[0]); // Size of array ^

    // ----- PORTS ----- //
    // Control Ports
    sc_signal<bool> tb_CTRL_ALU_REG_1, tb_CTRL_ALU_REG_2, tb_CTRL_DM_RW, tb_CTRL_RF_WRITE; 
    sc_signal<sc_bv<2> > tb_CTRL_PC_SRC, tb_CTRL_RESULT_SELECT;
    sc_signal<sc_bv<4> > tb_flags, tb_rdest_addr_rd, tb_rsrc_addr, tb_rdest_addr_wb;
    sc_signal<sc_bv<5> > tb_CTRL_ALU_OPCODE;
    sc_signal<sc_bv<8> > tb_immediate_in;
    sc_signal<sc_bv<16> > tb_instruction, tb_pc_next_if, tb_rdest_data_in, tb_rsrc_data_in, tb_jmp_tgt, tb_rsrc_data_out, tb_rdest_data_out, tb_alu_result_exe, tb_alu_result_mem, tb_data_in, tb_data_dm, tb_pc_next_wb, tb_alu_result_wb, tb_data_wb, tb_branch_disp, tb_final_result; 

    // ----- MODULES ----- //
    CTRL CTRL("CTRL");
    IM<sc_bv<16> > IM("IM", im_instr, im_instr_size); 
    RF<sc_bv<16> > RF("RF", rf_data, rf_data_size); 
    ALU ALU("ALU");
    DM<sc_bv<16> > DM("DM", dm_data, dm_data_size);
    monitor_CTRL monitor("CTRL_monitor");

    // ----- SIGNAL ASSOCIATION ----- //
    CTRL(tb_clock, tb_instruction, tb_pc_next_if, tb_flags, tb_rdest_addr_rd, tb_rsrc_addr, tb_rdest_data_in, tb_rsrc_data_in, tb_CTRL_ALU_REG_1, tb_CTRL_ALU_REG_2, tb_CTRL_ALU_OPCODE, tb_CTRL_PC_SRC, tb_jmp_tgt, tb_rsrc_data_out, tb_rdest_data_out, tb_immediate_in, tb_alu_result_exe, tb_CTRL_DM_RW, tb_alu_result_mem, tb_data_in, tb_data_dm, tb_CTRL_RF_WRITE, tb_CTRL_RESULT_SELECT, tb_rdest_addr_wb, tb_pc_next_wb, tb_alu_result_wb, tb_data_wb);
    IM(tb_clock, tb_CTRL_PC_SRC, tb_branch_disp, tb_jmp_tgt, tb_instruction, tb_pc_next_if);    
    RF(tb_clock, tb_CTRL_RF_WRITE, tb_rdest_addr_rd, tb_rsrc_addr, tb_rdest_addr_wb, tb_final_result, tb_rdest_data_in, tb_rsrc_data_in);
    ALU(tb_CTRL_ALU_REG_1, tb_CTRL_ALU_REG_2, tb_CTRL_ALU_OPCODE, tb_rdest_data_out, tb_rsrc_data_out, tb_immediate_in, tb_flags, tb_branch_disp, tb_alu_result_exe);
    DM(tb_clock, tb_CTRL_DM_RW, tb_CTRL_RESULT_SELECT, tb_alu_result_mem, tb_alu_result_wb, tb_pc_next_wb, tb_data_in, tb_data_wb, tb_data_dm, tb_final_result);
    monitor(tb_instruction, tb_pc_next_if, tb_flags, tb_rdest_addr_rd, tb_rsrc_addr, tb_rdest_data_in, tb_rsrc_data_in, tb_CTRL_ALU_REG_1, tb_CTRL_ALU_REG_2, tb_CTRL_ALU_OPCODE, tb_CTRL_PC_SRC, tb_jmp_tgt, tb_rsrc_data_out, tb_rdest_data_out, tb_immediate_in, tb_alu_result_exe, tb_branch_disp, tb_CTRL_DM_RW, tb_alu_result_mem, tb_data_in, tb_data_dm, tb_CTRL_RF_WRITE, tb_CTRL_RESULT_SELECT, tb_rdest_addr_wb, tb_pc_next_wb, tb_alu_result_wb, tb_data_wb, tb_final_result);

    // ----- TRACE FILE ----- //
    sc_trace_file *trace_file = sc_create_vcd_trace_file("mini_risc_processor");

    // ----- SIGNAL TRACE ----- //
    sc_trace(trace_file, tb_clock, "tb_clock");
    sc_trace(trace_file, tb_instruction, "tb_clear");
    sc_trace(trace_file, tb_pc_next_if, "tb_reset");
    sc_trace(trace_file, tb_flags, "tb_input");
    sc_trace(trace_file, tb_rdest_addr_rd, "tb_output");
    sc_trace(trace_file, tb_rsrc_addr, "tb_clear");
    sc_trace(trace_file, tb_rdest_data_in, "tb_reset");
    sc_trace(trace_file, tb_rsrc_data_in, "tb_input");
    sc_trace(trace_file, tb_CTRL_ALU_REG_1, "tb_output");
    sc_trace(trace_file, tb_CTRL_ALU_REG_2, "tb_clear");
    sc_trace(trace_file, tb_CTRL_ALU_OPCODE, "tb_reset");
    sc_trace(trace_file, tb_CTRL_PC_SRC, "tb_input");
    sc_trace(trace_file, tb_jmp_tgt, "tb_output");
    sc_trace(trace_file, tb_rsrc_data_out, "tb_clear");
    sc_trace(trace_file, tb_rdest_data_out, "tb_reset");
    sc_trace(trace_file, tb_immediate_in, "tb_input");
    sc_trace(trace_file, tb_alu_result_exe, "tb_output");
    sc_trace(trace_file, tb_branch_disp, "tb_clear");
    sc_trace(trace_file, tb_CTRL_DM_RW, "tb_reset");
    sc_trace(trace_file, tb_alu_result_mem, "tb_input");
    sc_trace(trace_file, tb_data_in, "tb_output");
    sc_trace(trace_file, tb_data_dm, "tb_clear");
    sc_trace(trace_file, tb_CTRL_RF_WRITE, "tb_reset");
    sc_trace(trace_file, tb_CTRL_RESULT_SELECT, "tb_input");
    sc_trace(trace_file, tb_rdest_addr_wb, "tb_output");
    sc_trace(trace_file, tb_pc_next_wb, "tb_input");
    sc_trace(trace_file, tb_alu_result_wb, "tb_output");
    sc_trace(trace_file, tb_data_wb, "tb_clear");
    sc_trace(trace_file, tb_final_result, "tb_reset");

    // ----- START ----- //
    sc_start(100, SC_NS);
    sc_close_vcd_trace_file(trace_file);

    return 0;
}
