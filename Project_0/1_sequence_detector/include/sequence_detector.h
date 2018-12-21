//============== SEQUENCE DETECTOR ==============
//
// File : sequence_detector.h
// Output 'HIGH' if sequence "1011" is detected.
//
//===============================================
#ifndef _SEQUENCE_DETECTOR_H
#define _SEQUENCE_DETECTOR_H
#include "systemc.h" 

template<typename T> 
class sequence_detector : public sc_module {
    public:
        // ----- PORTS ----- //
        sc_in <T> Clock, Reset, Clear, Input;
        sc_out <T> Output;
        
        // ----- INTERNAL VARIABLES ----- //
        sc_signal <T> first, second, third, fourth; 

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(sequence_detector);
            sequence_detector(sc_module_name name) : sc_module(name) {
                SC_METHOD(process_sequence_detector);
	                sensitive << Clock.pos();
	            SC_METHOD(process_output);
	                sensitive << first << second << third << fourth << Clear;
            }
    private:
        // ----- METHODS ----- //
        void process_sequence_detector();
        void process_output();
};
#endif
