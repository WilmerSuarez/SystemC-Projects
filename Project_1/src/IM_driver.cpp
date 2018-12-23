//============== MINI RISC PROCESSOR ============= //
//
// File : IM_driver.cpp
// Drives bits going into the Instruction Memory.
//
//================================================ //
#include "IM_driver.h"

void driver_IM::process_driver_IM() {
    driver_CTRL_PC_SRC = "00";
    driver_branch_disp = 0x0000;
    driver_jmp_target = 0x0000;

    while(true) {
        wait(4); // Wait 4 clk triggers
        driver_jmp_target = 0x0000;
        wait(5); // Wait 5 clk triggers
        driver_branch_disp = -2;
        driver_CTRL_PC_SRC = "01";
        wait(2);
        driver_CTRL_PC_SRC = "10";
        wait(10);
    }
}
