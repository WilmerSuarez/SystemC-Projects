//============ MINI RISC PROCESSOR =========== //
//
// File : RF_driver.cpp
// Drives bits going into the Register File.
//
//============================================ //
#include "RF_driver.h"

void driver_RF::process_driver_RF() {
    driver_CTRL_RF_WRITE = 0;
    driver_data_in = 0xBEEF;
    int i = 0;

    /*while(true) {
        wait();
        driver_rdest_addr = i;
        driver_rsrc_addr = ++i;
    }*/

    while(true) {
        wait();
        driver_CTRL_RF_WRITE = 1;
        driver_wb_reg = 0xF;
        wait();
        driver_CTRL_RF_WRITE = 0;
        driver_rdest_addr = 0xF;
        wait(10);
    }
}
