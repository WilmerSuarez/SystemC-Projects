//============== SEQUENCE DETECTOR ==============
//
// File : sequence_detector.cpp
// Output 'HIGH' if sequence "1011" is detected.
//
//===============================================
#include "sequence_detector.h"

template<class T>
void sequence_detector<T>::process_sequence_detector() {
    if(Reset == 0) {
        first = 0;
	    second = 0;
	    third = 0;
	    fourth = 0;
    } else { 
        first = Input;
        second = first;
        third = second;
        fourth = third;
    }
}

template<class T>
void sequence_detector<T>::process_output() {
    if(Clear == 1) {
        Output = 0;
    } else {
        Output = first & ~(second) & third & fourth;
    }
}
