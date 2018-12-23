//============== MINI RISC PROCESSOR ============= //
//
// File : IM_monitor.cpp
// Monitor Instruction Memory inputs and outputs.
//
//================================================ //
#include "IM_monitor.h"

void monitor_IM::process_monitor_IM() {
    cout << "@: " << sc_time_stamp() << "\n";
    printf(" CTRL_PC_SRC: %d\n", monitor_CTRL_PC_SRC.read().to_uint());
    printf(" branch_disp: 0x%02X\n", monitor_branch_disp.read().to_int());
    printf(" jmp_target: 0x%02X\n", monitor_jmp_target.read().to_int());
    printf(" instruction: 0x%02X\n", monitor_instruction.read().to_int());
    printf(" pc_next: 0x%02X\n", monitor_pc_next.read().to_int());
}
