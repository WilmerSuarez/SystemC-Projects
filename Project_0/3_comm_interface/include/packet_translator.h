//=== COMMUNICATION INTERFACE ===//
//
// File : packet_translator.h
//
//===============================//
#include "systemc.h"

SC_MODULE(packet_translator) {
    // ===== PORTS ===== //
    sc_in <bool> clock, reset, clear;
    sc_in <sc_uint<12> > in_data;
    sc_out <sc_uint<8> > count, error;
    sc_out <sc_uint<4> > payload;
  
    // ===== INTERNAL VARIABLE ===== //
    sc_uint<8> count_temp, error_temp;

    // ===== METHODS ===== //
    void process_packet_translator();

    // ===== CONSTRUCTOR ===== //
    SC_CTOR(packet_translator) {
        SC_METHOD(process_packet_translator);
	    sensitive << clock.pos();
    }
};
