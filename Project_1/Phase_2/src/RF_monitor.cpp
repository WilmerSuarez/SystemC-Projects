//============ MINI RISC PROCESSOR =========== //
//
// File : RF_monitor.cpp
// Monitor Register File inputs and outputs.
//
//============================================ //
#include "RF_monitor.h"

void monitor_RF::process_monitor_RF() {
    cout << "@: " << sc_time_stamp() << "\n";
    cout << " CTRL_RF_WRITE: " << monitor_CTRL_RF_WRITE.read() << endl;
    printf(" rdest_addr: 0x%04X\n", monitor_rdest_addr.read().to_int());
    printf(" rsrc_addr: 0x%04X\n", monitor_rsrc_addr.read().to_int());
    printf(" wb_reg: 0x%04X\n", monitor_wb_reg.read().to_int());
    printf(" data_in: 0x%04X\n", monitor_data_in.read().to_int());
    printf(" rdest_data: 0x%04X\n", monitor_rdest_data.read().to_int());
    printf(" rsrc_data: 0x%04X\n", monitor_rsrc_data.read().to_int());
}