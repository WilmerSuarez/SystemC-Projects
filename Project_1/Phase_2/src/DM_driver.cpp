//============ MINI RISC PROCESSOR =========== //
//
// File : DM_driver.cpp
// Drives bits going into the Data Memory.
//
//============================================ //
#include "DM_driver.h"

void driver_DM::process_driver_DM() {
    driver_CTRL_DM_RW = 0;
    driver_CTRL_RESULT_SELECT = "00";
    driver_data_in = 0xBEEF;
    size_t i = 0;

    while(true) {
        wait();
        driver_alu_result = 0xDEAD;
        driver_dm_addr = ++i;
        wait();
        driver_CTRL_RESULT_SELECT = 1;
        driver_pc_next = 0xBEED;
        wait();
        driver_CTRL_RESULT_SELECT = 2;
        driver_dm_result = 0xDEED;
        driver_CTRL_DM_RW = 1;
        wait();
        driver_CTRL_RESULT_SELECT = 0;
        driver_CTRL_DM_RW = 0;
        wait();
        driver_CTRL_RESULT_SELECT = 1;
        wait();
        driver_CTRL_RESULT_SELECT = 2;
        wait(10);
    }
}
