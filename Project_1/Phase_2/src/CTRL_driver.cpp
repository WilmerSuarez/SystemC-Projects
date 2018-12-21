//============== MINI RISC PROCESSOR ============= //
//
// File : CTRL_driver.cpp
// Drives bits going into the Control Module.
//
//================================================ //
#include "CTRL_driver.h"

void driver_CTRL::process_driver_CTRL() {
    driver_flags = 0x0000;
    uint i = 0;

    while(true) {
        wait();
        driver_instruction = 0x1000; 
    }
}