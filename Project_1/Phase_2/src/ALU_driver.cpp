//============== MINI RISC PROCESSOR ============= //
//
// File : ALU_driver.cpp
// Drives bits going into the ALU.
//
//================================================ //
#include "ALU_driver.h"

void driver_ALU::process_driver_ALU() {
    driver_CTRL_ALU_REG_1 = 1;
    driver_CTRL_ALU_REG_2 = 1;
    driver_immediate_in = 0x029;
    driver_rdest_data = 0x1308;
    driver_rsrc_data = 0x1308;

    while(true) {
        wait();
        driver_CTRL_ALU_OPCODE = 0x04;
    }
}
