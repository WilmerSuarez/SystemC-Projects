// ============ MINI RISC PROCESSOR ============ //
// 
// File : RF.h
// This module contains 16, 16-bit registers 
// used to store the data being manipulated 
// by the ALU. 
//
// ============================================= //
#ifndef RF_H
#define RF_H
#include "systemc.h"

#define RF_SIZE 16

template<typename T> 
class RF : public sc_module {
    public: 
        // ----- PORTS ----- //
        sc_in_clk clk;                  // Clock
        sc_in<bool> CTRL_RF_WRITE;      // Write enable for Register File - Control Signal
        sc_in<sc_bv<4> > rdest_addr;    // Register File destination register address
        sc_in<sc_bv<4> > rsrc_addr;     // Register File source register address
        sc_in<sc_bv<4> > wb_reg;        // Address of register to be written
        sc_in<sc_bv<16> > data_in;      // Data to be written 
        sc_out<sc_bv<16> > rdest_data;  // Data from Rdest register
        sc_out<sc_bv<16> > rsrc_data;   // Data from Rsrc register
        
        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(RF);
            RF(sc_module_name name, const T* rf_data, const size_t size) 
                : sc_module(name), 
                  _rf_data(rf_data), 
                  _size(size) {

                // Read and output Instruction data on every Positive Edge.
                SC_CTHREAD(RF_proc_read, clk.pos());

                // Write to Writeback Register on Negative Edge, if CTRL_RF_WRITE is asserted.
                SC_CTHREAD(RF_proc_write, clk.neg());

                // Fill Register File with data
                for(unsigned i = 0; i < _size; ++i) {
                    _register_file[i] = *(_rf_data + i);
                }
            }
    private:
         // ----- INTERNAL VARIABLES ----- //
        const T* _rf_data;                      // Array of 16-bit data 
        const size_t _size;                     // Size of arry of 16-bit data
        T _register_file[RF_SIZE];               // Register File buffer - Initialized to 0

        // ----- INTERNAL SIGNALS ----- //
        sc_uint<4> _rdest_addr;         // Destination Register Address
        sc_uint<4> _rsrc_addr;          // Source Register Address
        sc_uint<4> _wb_reg_addr;        // Write Back Register Address

        // ----- METHODS ----- //
        void RF_proc_read();            // Register File Process
        void RF_proc_write();           // Register File Process
};
#endif
