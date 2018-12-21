//====== COUNTER ======//
//
// File : monitor.cpp
//
//=====================//
#include "monitor.h"

void monitor::process_monitor() {
    cout << "@: " << sc_time_stamp() << "\n";
    cout << "In_1: " << monitor_in_1;
    cout << " In_2: " << monitor_in_2;
    cout << " In_3: " << monitor_in_3;
    cout << " Load_1: " << monitor_load_1;
    cout << " Load_2: " << monitor_load_2;
    cout << " Dec_1: " << monitor_dec_1;
    cout << " Dec_2: " << monitor_dec_2;
    cout << " Overflow_1: " << monitor_overflow_1;
    cout << " Overflow_2: " << monitor_overflow_2;
    cout << " Count_1: " << monitor_count_1;
    cout << " Count_2: " << monitor_count_2;
    cout << " Ended: " << monitor_ended << "\n";
}
