//============== MINI RISC PROCESSOR ============= //
//
// File : CTRL_monitor.cpp
// Monitor Control Module inputs and outputs.
//
//================================================ //
#include "CTRL_monitor.h"

void monitor_CTRL::process_monitor_CTRL() {
    cout << "@: " << sc_time_stamp() << "\n";
    printf("IF Stage\n");
    printf(" monitor_instruction: 0x%02X\n", monitor_instruction.read().to_int());
    printf(" monitor_pc_next_if: 0x%02X\n", monitor_pc_next_if.read().to_int());
    printf(" monitor_flags: 0x%02X\n", monitor_flags.read().to_int());
    printf("RD Stage\n");
    printf(" monitor_rdest_addr_rd: 0x%02X\n", monitor_rdest_addr_rd.read().to_int());
    printf(" monitor_rsrc_addr: 0x%02X\n", monitor_rsrc_addr.read().to_int());
    printf(" monitor_rdest_data_in: 0x%02X\n", monitor_rdest_data_in.read().to_int());
    printf(" monitor_rsrc_data_in: 0x%02X\n", monitor_rsrc_data_in.read().to_int());
    printf("EXE Stage\n");
    cout << " CTRL_ALU_REG_1: " << monitor_CTRL_ALU_REG_1.read() << endl;
    cout << " CTRL_ALU_REG_2: " << monitor_CTRL_ALU_REG_2.read() << endl;
    printf(" monitor_CTRL_ALU_OPCODE: 0x%02X\n", monitor_CTRL_ALU_OPCODE.read().to_int());
    printf(" monitor_CTRL_PC_SRC: 0x%02X\n", monitor_CTRL_PC_SRC.read().to_int());
    printf(" monitor_jmp_tgt: 0x%02X\n", monitor_jmp_tgt.read().to_int());
    printf(" monitor_rdest_data_out: 0x%02X\n", monitor_rdest_data_out.read().to_int());
    printf(" monitor_rsrc_data_out: 0x%02X\n", monitor_rsrc_data_out.read().to_int());
    printf(" monitor_immediate: 0x%02X\n", monitor_immediate.read().to_int());
    printf(" monitor_alu_result_exe: 0x%02X\n", monitor_alu_result_exe.read().to_int());
    printf(" monitor_branch_disp: 0x%02X\n", monitor_branch_disp.read().to_int());
    printf("MEM Stage\n");
    cout << " monitor_CTRL_DM_RW " << monitor_CTRL_DM_RW.read() << endl;
    printf(" monitor_alu_result_mem: 0x%02X\n", monitor_alu_result_mem.read().to_int());
    printf(" monitor_data_in: 0x%02X\n", monitor_data_in.read().to_int());
    printf(" monitor_data_dm: 0x%02X\n", monitor_data_dm.read().to_int());
    printf("WB Stage\n");
    cout << " monitor_CTRL_RF_WRITE " << monitor_CTRL_RF_WRITE.read() << endl;
    printf(" monitor_CTRL_RESULT_SELECT: 0x%02X\n", monitor_CTRL_RESULT_SELECT.read().to_int());
    printf(" monitor_rdest_addr_wb: 0x%02X\n", monitor_rdest_addr_wb.read().to_int());
    printf(" monitor_pc_next_wb: 0x%02X\n", monitor_pc_next_wb.read().to_int());
    printf(" monitor_alu_result_wb: 0x%02X\n", monitor_alu_result_wb.read().to_int());
    printf(" monitor_data_wb: 0x%02X\n", monitor_data_wb.read().to_uint());
    printf(" monitor_final_result: 0x%02X\n", monitor_final_result.read().to_uint());
}
