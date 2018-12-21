// ============ MINI RISC PROCESSOR ============ //
// 
// File : CTRL.h
// This modules directs the processor datapath
// operation. It tells the other modules how to
// respond to the instructions being executed.
// It provides the pipelining and control signals 
// for the datapath.  
//
// ============================================= //
#ifndef CTRL_H
#define CTRL_H
#include "systemc.h"
#include "defs.h"

// Pipeline stage sizes
#define IF_RD_SIZE      11
#define RD_EXE_SIZE     12
#define EXE_MEM_SIZE    7
#define MEM_WB_SIZE     6

// Branch/Jump Conditions
#define EQ  0x0
#define NE  0x1
#define GE  0xD
#define CS  0x2
#define CC  0x3
#define HI  0x4
#define LS  0x5
#define LO  0xA
#define HS  0xB
#define GT  0x6
#define LE  0x7
#define FS  0x8
#define FC  0x9
#define LT  0xC
#define US  0xE

// ----- PIPELINE ENTRY INDEXES ----- //
// IF/RD
#define RESULT_SELECT_RD   0
#define DATA_RW_RD         1
#define PC_SRC_RD          2
#define ALU_OPCODE_RD      3
#define ALU_REG_1_RD       4
#define ALU_REG_2_RD       5
#define RF_WRITE_RD        6
#define PCP2_RD            7
#define RDEST_ADDR_RD      8
#define RSRC_ADDR_RD       9
#define IMMEDIATE_RD       10
// RD/EXE
#define RF_WRITE_EXE       0
#define RESULT_SELECT_EXE  1
#define DATA_RW_EXE        2
#define PC_SRC_EXE         3
#define ALU_OPCODE_EXE     4
#define ALU_REG_1_EXE      5
#define ALU_REG_2_EXE      6
#define PCP2_EXE           7
#define RDEST_ADDR_EXE     8
#define IMMEDIATE_EXE      10
#define RDEST_DATA_EXE     11
#define RSRC_DATA_EXE      12
// EXE/MEM
#define RF_WRITE_MEM       0
#define RDEST_ADDR_MEM     1
#define RESULT_SELECT_MEM  2
#define DATA_RW_MEM        3
#define PCP2_MEM           4
#define RDEST_DATA_MEM     5
#define ALU_RES_MEM        6
// MEM/WB
#define RF_WRITE_WB        0
#define RDEST_ADDRESS_WB   1
#define RESULT_SELECT_WB   2
#define PCP2_WB            3
#define ALU_RES_WB         4
#define DATA_OUT_WB        5

class CTRL : public sc_module {
    public: 
        // ----- PORTS ----- //
        sc_in_clk clk;
        // IF Stage
        sc_in<sc_bv<16> > instruction;          // Instruction bits - Used to generate control signals
        sc_in<sc_bv<16> > pc_next_if;           // Next instruction address (PC + 2)
        sc_in<sc_bv<4> > flags;                 // Flags produced by the ALU to evaluate jump/branch 
        // RD Stage
        sc_out<sc_bv<4> > rdest_addr_rd;        // Register File destination register address - read
        sc_out<sc_bv<4> > rsrc_addr;            // Register File source register address - read
        sc_in<sc_bv<16> > rdest_data_in;        // Data from rdest register
        sc_in<sc_bv<16> > rsrc_data_in;         // Data from rsrc register
        // EXE Stage
        sc_out<bool> CTRL_ALU_REG_1;            // Mux select for the first operand of the ALU - Control Signal 
        sc_out<bool> CTRL_ALU_REG_2;            // Mux select for the second operand of the ALU - Control Signal
        sc_out<sc_bv<5> > CTRL_ALU_OPCODE;      // Alu Opcode, lets the ALU know what function to perform - Control Signal
        sc_out<sc_bv<2> > CTRL_PC_SRC;          // PC input mux select - Control Signal
        sc_out<sc_bv<16> > jmp_tgt;             // Data from Register File rsrc register - JCOND Instruction target
        sc_out<sc_bv<16> > rsrc_data_out;       // Data from Register File rsrc register - ALU operand
        sc_out<sc_bv<16> > rdest_data_out;      // Data from Register File rdest register - ALU operand
        sc_out<sc_bv<8> > immediate;            // Instruction extracted 8-bit immediate
        sc_in<sc_bv<16> > alu_result_exe;       // Result from ALU
        // MEM Stage
        sc_out<bool> CTRL_DM_RW;                // Enables writing to the Data Memory - Control Signal
        sc_out<sc_bv<16> > alu_result_mem;      // Result from ALU - to be used as Data Memory address
        sc_out<sc_bv<16> > data_in;             // Data from Rdest register - to be stored in Data Memory (SOTR Instruction)
        sc_in<sc_bv<16> > data_dm;              // Data read from Data Memory
        // WB Stage
        sc_out<bool> CTRL_RF_WRITE;             // Write enable for Register File - Control Signal
        sc_out<sc_bv<2> > CTRL_RESULT_SELECT;   // Selects final result - ALU result or DM entry - Control Signal
        sc_out<sc_bv<4> > rdest_addr_wb;        // Register File destination register address - write
        sc_out<sc_bv<16> > pc_next_wb;          // Address of Next instruction - Used for JAL Instruction
        sc_out<sc_bv<16> > alu_result_wb;       // Result from ALU - To be used as Final result to be written to Register File
        sc_out<sc_bv<16> > data_wb;             // Data read from Data Memory - To be used as Final result to be written to Register File

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(CTRL);
            CTRL(sc_module_name name) 
                : sc_module(name) {
                
                // Process instructions and Control/Module Signals
                SC_CTHREAD(CTRL_proc, clk.pos());
                SC_METHOD(CTRL_proc_instr);
                    sensitive << instruction;
            }
    private:
        // ----- METHODS ----- //
        void CTRL_proc();                          // Provide Control Synchronization between all modules
        void CTRL_proc_instr();                    // Decode Instruction
        bool CTRL_brnch_jmp_cond_check(sc_bv<4>);  // Check the condition of the branch or jump

        // ----- INTERNAL SIGNALS ----- //
        // ----- PIPELINE REGISTERS ----- //
        sc_signal <sc_bv<16> > _IF_RD_stage[IF_RD_SIZE];                     // IF/RD Pipeline
        sc_signal <sc_bv<16> > _RD_EXE_stage[RD_EXE_SIZE];      // RD/EXE Pipeline
        sc_signal <sc_bv<16> > _EXE_MEM_stage[EXE_MEM_SIZE];    // EXE/MEM Pipeline
        sc_signal <sc_bv<16> > _MEM_WB_stage[MEM_WB_SIZE];      // MEM/WB Pipeline
        
        // ----- INTERNAL VARIABLES ----- //
        sc_bv<16> _instruction;     // 16-bit instruction. Decoded to get control signals
        sc_bv<4> _flags;              // Conditional Instruction Flags
};

#endif // CTRL_H
