//====== COUNTER ======//
//
// File : counter_2.cpp
//
//=====================//
#include "counter_2.h"

void counter_2::process_count_2() {
    if(load_2) {
        count_prev_2 = in_2.read();
        temp_2 = count_prev_2;
    } else if(dec_2) {
        temp_2 = count_prev_2;
        count_prev_2 -= in_3.read();
    }
    
    count_2 = count_prev_2;

    if(count_prev_2 > temp_2) {
        overflow_2 = 1;
    }
}
