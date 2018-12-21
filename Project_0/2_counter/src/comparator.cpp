//====== COUNTER ======//
//
// File : comparator.cpp
//
//=====================//
#include "comparator.h"

void comparator::process_comparator() {
    if((count_1 == count_2) || overflow_1 || overflow_2) {
        ended = 1; 
    } else {
	ended = 0;
    }	    
}
