// ============== ROBOT NAVIGATION ============== //
// 
// File : monitor.h
// This module monitors the inputs and outputs of 
// the Robot Navigation System.
//
// ============================================== //
#include "monitor.h"

void monitor::monitor_proc() {
    cout << "@: " << sc_time_stamp() << "\n";
    cout << " monitor_packet_validS: " << monitor_packet_validS.read() << endl;
    cout << " monitor_packet_validE: " << monitor_packet_validE.read() << endl;
    cout << " monitor_packet_fromE: " << monitor_packet_fromE.read() << endl;
    cout << " monitor_packet_fromS: " << monitor_packet_fromS.read() << endl;
    cout << " monitor_packet_toE: " << monitor_packet_toE.read() << endl;
    cout << " monitor_packet_toS: " << monitor_packet_toS.read() << endl;
}
