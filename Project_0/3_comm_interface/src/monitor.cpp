//=== COMMUNICATION INTERFACE ===//
//
// File : monitor.cpp
//
//===============================//
#include "monitor.h"

void monitor::process_monitor() {
    cout << "@: " << sc_time_stamp() << "\n";
    cout << " Reset: " << monitor_reset;
    cout << " Clear: " << monitor_clear;
    cout << " InData: " << monitor_in_data;
    cout << " Count: " << monitor_count;
    cout << " Error: " << monitor_error;
    cout << " Payload: " << monitor_payload << "\n";
}
