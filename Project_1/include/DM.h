// ============ MINI RISC PROCESSOR ============ //
// 
// File : DM.h
// This module is the general purpose RAM. 
// Stores data for the executing program.
//
// ============================================= //
#ifndef DM_H
#define DM_H
#include "systemc.h"

#define _ALU_RESULT 0
#define JAL_LINK 1
#define DM_OUT 2
#define ADDR_WIDTH 16

template<typename T, size_t M_SIZE = (1 << ADDR_WIDTH)> 
class DM : public sc_module {
    public: 
        // ----- PORTS ----- //
        sc_in_clk clk;                        // Clock
        sc_in<bool> CTRL_DM_RW;               // Enables writing to the Data Memory - Control Signal
        sc_in<sc_bv<2> > CTRL_RESULT_SELECT;  // Selects final result - ALU result or DM entry - Control Signal
        sc_in<sc_bv<16> > dm_addr;            // ALU result - used as DM address
        sc_in<sc_bv<16> > alu_result;         // ALU result - calculation result to be written back to Register File
        sc_in<sc_bv<16> > pc_next;            // Address of Next instruction - Used for JAL Instruction
        sc_in<sc_bv<16> > data_in;            // Data to be written into Data Memory when writing to it is enabled
        sc_in<sc_bv<16> > dm_result;          // Data read from the Data Memory - to be written back to Reigster File
        sc_out<sc_bv<16> > data_out;          // Data read from the Data Memory
        sc_out<sc_bv<16> > final_result;      // Final result to be written back to Register File

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(DM);
            DM(sc_module_name name, const T* dm_data, const size_t size) 
                : sc_module(name), 
                _dm_data(dm_data), 
                _size(size) {
                    
                SC_CTHREAD(DM_proc, clk.pos());

                SC_METHOD(final_result_proc);
                    sensitive << CTRL_RESULT_SELECT << alu_result << pc_next << dm_result;

                // Fill Data Memory with data
                for(unsigned i = 0; i < _size; ++i) {
                  _data_memory[i] = *(_dm_data + i);
                }
            }
    private:
        // ----- INTERNAL VARIABLES ----- //
        const T* _dm_data;                     // Array of 16-bit data 
        const size_t _size;                    // Size of array of 16-bit data
        T _data_memory[M_SIZE];                // Data Memory Storage - Initialized to 0
    
        // ----- INTERNAL SIGNALS ----- //
        sc_signal<sc_uint<16> > _dm_address;        // ALU result (DM access address)
        //sc_signal<sc_uint<16> > _dm_result;         // Output of data memory read
        sc_signal<sc_uint<16> > _alu_result_mux;    // Result from ALU computation
        sc_signal<sc_uint<16> > _jal_link;          // Next PC address used by JAL instruction
        sc_signal<sc_uint<16> > _dm_result_mux;     // Final result - from data memory

        // ----- METHODS ----- //
        void DM_proc();                 // Data Memory Process
        void final_result_proc();       // Final result mux process
};
#endif
