//============ MINI RISC PROCESSOR =========== //
//
// File : DM_monitor.cpp
// Monitor Data Memory inputs and outputs.
//
//============================================ //
#include "DM_monitor.h"

void monitor_DM::process_monitor_DM() {
    cout << "@: " << sc_time_stamp() << "\n";
    cout << " CTRL_DM_RW: " << monitor_CTRL_DM_RW.read() << endl;
    printf(" CTRL_RESULT_SELECT: 0x%04X\n", monitor_CTRL_RESULT_SELECT.read().to_int());
    printf(" dm_addr: 0x%04X\n", monitor_dm_addr.read().to_int());
    printf(" alu_result: 0x%04X\n", monitor_alu_result.read().to_int());
    printf(" pc_next: 0x%04X\n", monitor_pc_next.read().to_int());
    printf(" data_in: 0x%04X\n", monitor_data_in.read().to_int());
    printf(" dm_result: 0x%04X\n", monitor_dm_result.read().to_int());
    printf(" data_out: 0x%04X\n", monitor_data_out.read().to_int());
    printf(" final_result: 0x%04X\n", monitor_final_result.read().to_int());
}