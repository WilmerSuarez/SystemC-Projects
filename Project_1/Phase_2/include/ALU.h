// ============ MINI RISC PROCESSOR ============ //
// 
// File : ALU.h
// This module performs the arithmetic and
// logic operations needed by the program 
// currently executing on the processor.
//
// ============================================= //
#ifndef ALU_H
#define ALU_H
#include "systemc.h"
#include "defs.h"

class ALU : public sc_module {
    public: 
        // ----- PORTS ----- //
        sc_in<bool> CTRL_ALU_REG_1;        // Mux select for the first operand of the ALU - Control Signal 
        sc_in<bool> CTRL_ALU_REG_2;        // Mux select for the second operand of the ALU - Control Signal
        sc_in<sc_bv<5> > CTRL_ALU_OPCODE;  // Alu Opcode, lets the ALU know what function to perform - Control Signal
        sc_in<sc_bv<16> > rdest_data;      // Data from the Register File from the register pointed to by rdest
        sc_in<sc_bv<16> > rsrc_data;       // Data from the Register File from the register pointed to by rsrc
        sc_in<sc_bv<8> > immediate_in;     // Instruction extracted 8-bit immediate
        sc_out<sc_bv<4> > flags;           // Flags produced by the ALU - Control bound
        sc_out<sc_bv<16> > immediate_out;  // Sign Extended 16-bit immediate - Branch Displacement
        sc_out<sc_bv<16> > alu_result;     // Result of the ALU operation

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(ALU);
            ALU(sc_module_name name) 
                : sc_module(name) {
                
                SC_METHOD(ALU_proc);
                    dont_initialize();
                    sensitive << CTRL_ALU_REG_1 << CTRL_ALU_REG_2 << CTRL_ALU_OPCODE;
                    sensitive << rdest_data << rsrc_data << immediate_in;
            }

    private:
        // ----- INTERNAL VARIABLES ----- //
        sc_int<16> _reg1_data;
        sc_int<16> _reg2_data;
        sc_uint<16> _immediate_extended_logic;
        sc_int<16> _immediate_extended_arithmetic;
        sc_uint<16> _alu_result;
        sc_uint<4> _psr;

        // ----- METHODS ----- //
        void ALU_proc();            // Register File Process
};

#endif // ALU_H
