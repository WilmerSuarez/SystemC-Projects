//====== COUNTER ======//
//
// File : driver.cpp
//
//=====================//
#include "driver.h"

void driver::process_driver() {
    in_1 = 7;
    in_2 = 10;
    in_3 = 4;
    load_1 = 1;
    load_2 = 1;
    wait(5, SC_NS); // Counter_1 = 7, Counter_2 = 10 for 5 ns
    
    load_1 = 0;
    load_2 = 0;
    dec_1 = 1;
    wait(1, SC_NS); // Counter_1 = 6
    dec_1 = 0;
    dec_2 = 1;
    wait(1, SC_NS); // Counter_2 = 6
    dec_2 = 0;
    wait(5, SC_NS); // ended = 1

    dec_1 = 1;
    dec_2 = 1;
    wait(5, SC_NS); // Overflow_1 = 1, Overflow_2 = 1;
    dec_1 = 0;
    dec_2 = 0;
    wait(10, SC_NS);
}
