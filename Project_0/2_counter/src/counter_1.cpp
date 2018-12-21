//====== COUNTER ======//
//
// File : counter_1.cpp
//
//=====================//
#include "counter_1.h"

void counter_1::process_count_1() {
    if(load_1) {
	count_prev_1 = in_1.read();
	temp_1 = count_prev_1;
    } else if(dec_1) { 
	temp_1 = count_prev_1;
	count_prev_1--;
    }
    
    count_1 = count_prev_1;

    if(count_prev_1 > temp_1) {
	overflow_1 = 1;
    }
}
