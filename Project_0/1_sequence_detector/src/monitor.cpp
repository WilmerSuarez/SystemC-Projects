//============== SEQUENCE DETECTOR ==============
//
// File : monitor.cpp
// Monitor sequence detector outputs and inputs
//
//===============================================
#include "monitor.h"

void monitor::process_monitor() {
    cout << "@: " << sc_time_stamp() << "\n";
    cout << " Reset: " << monitor_reset;
    cout << " Clear: " << monitor_clear;
    cout << " Input: " << monitor_input;
    cout << " Output: " << monitor_output << "\n";
}
