//============== MINI RISC PROCESSOR ============= //
//
// File : ALU_monitor.cpp
// Monitor ALU inputs and outputs.
//
//================================================ //
#include "ALU_monitor.h"

void monitor_ALU::process_monitor_ALU() {
    cout << "@: " << sc_time_stamp() << "\n";
    cout << " CTRL_ALU_REG_1: " << monitor_CTRL_ALU_REG_1.read() << endl;
    cout << " CTRL_ALU_REG_2: " << monitor_CTRL_ALU_REG_2.read() << endl;
    printf(" monitor_flags: 0x%02X\n", monitor_flags.read().to_int());
    printf(" CTRL_ALU_OPCODE: 0x%02X\n", monitor_CTRL_ALU_OPCODE.read().to_int());
    printf(" immediate_in: 0x%02X\n", monitor_immediate_in.read().to_int());
    printf(" rdest_data: 0x%02X\n", monitor_rdest_data.read().to_uint());
    printf(" rsrc_data: 0x%02X\n", monitor_rsrc_data.read().to_int());
    printf(" immediate_out: 0x%02X\n", monitor_immediate_out.read().to_int());
    printf(" alu_result: 0x%04X\n", monitor_alu_result.read().to_int());
}
