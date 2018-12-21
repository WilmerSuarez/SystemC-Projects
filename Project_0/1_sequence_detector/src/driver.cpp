//============== SEQUENCE DETECTOR ==============
//
// File : driver.cpp
// Drives bits going into the sequence detector
//
//===============================================
#include "driver.h"

void driver::process_driver() {
    driver_reset = 1;
    driver_clear = 0;
    
    while(1) {
    	driver_input = 1;
    	wait(1, SC_NS);
    	driver_input = 0;
    	wait(1, SC_NS);
    	driver_input = 1;
    	wait(1, SC_NS);
    	driver_input = 1;
    	wait(1, SC_NS);
    }
}
