// ============ MINI RISC PROCESSOR ============ //
// 
// File : IM.h
// This module stores the instructions of the 
// program currently executing on the Processor.
//
// ============================================= //
#ifndef IM_H
#define IM_H
#include "systemc.h"

#define ADDR_WIDTH  16
#define PCP2        0
#define BRANCH      1
#define JUMP        2

template<typename T, size_t M_SIZE = (1 << ADDR_WIDTH)> 
class IM : public sc_module {
    public: 
        // ----- PORTS ----- //
        sc_in_clk clk;                      // Clock
        sc_in<sc_bv<2> > CTRL_PC_SRC;       // PC input mux select - Control Signal
        sc_in<sc_bv<16> > branch_disp;      // Branch displacement - Signed Extended immediate
        sc_in<sc_bv<16> > jmp_target;       // Jump Target - Rsrc data
        sc_out<sc_bv<16> > instruction;     // Control bound 16-bit instruction
        sc_out<sc_bv<16> > pc_next;         // Next instruction address (PC + 2)

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(IM);
            IM(sc_module_name name, const T* im_instr, const size_t size) 
                : sc_module(name),
                 _im_instr(im_instr), 
                 _size(size) {

                // Update Program Counter on every Positive Clock edge
                SC_CTHREAD(IM_proc, clk.pos());

                // Fill Instruction Memory with instructions
                for(unsigned i = 0; i < _size; ++i) {
                    _instruction_memory[i] = *(_im_instr + i);
                }
            }
    private:
        // ----- INTERNAL VARIABLES ----- //
        const T* _im_instr;                        // Array of instruction data 
        const size_t _size;                        // Size of array of instruction data
        T _instruction_memory[M_SIZE];             // Instruction Memory buffer - Initialized to 0
        sc_uint<16> _pc_next;                      // Next address output of the Program Counter

        // ----- INTERNAL SIGNALS ----- //
        sc_signal<sc_uint<16> > _im_address;       // Current Program Counter output
        sc_signal<sc_int<16> > _branch_disp;       // Branch displacement integer
        
        // ----- METHODS ----- //
        void IM_proc();                            // Instruction Memory Process
};

#endif // IM_H
