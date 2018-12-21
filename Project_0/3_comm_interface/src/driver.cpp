//=== COMMUNICATION INTERFACE ===//
//
// File : driver.cpp
//
//===============================//
#include "driver.h"

void driver::process_driver() {
    driver_reset = 1;
    driver_clear = 0;

    driver_in_data = 0x1F1;
    wait(1, SC_NS);
    driver_in_data = 0x0E0;
    wait(1, SC_NS);
    driver_in_data = 0x171;
    wait(1, SC_NS);
    driver_in_data = 0x190;
    wait(1, SC_NS);
}
