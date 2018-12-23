// ============ MINI RISC PROCESSOR ============ //
// 
// File : CTRL.cpp
// This modules directs the processor datapath
// operation. It tells the other modules how to
// respond to the instructions being executed.
// It provides the pipelining and control signals 
// for the datapath.  
//
// ============================================= //
#include "CTRL.h"

void CTRL::CTRL_proc_instr() {
    // Read and decode instruction
    _instruction = instruction.read();

    // General Control Signals for each instruction
    _IF_RD_stage[RESULT_SELECT_RD] = 0x0000;
    _IF_RD_stage[DATA_RW_RD] = 0x0000;
    _IF_RD_stage[PC_SRC_RD] = 0x0000;
    _IF_RD_stage[ALU_REG_1_RD] = 0x0000;
    _IF_RD_stage[ALU_REG_2_RD] = 0x0000;
    _IF_RD_stage[RF_WRITE_RD] = 0x0000;
    _IF_RD_stage[PCP2_RD] = pc_next_if.read();
    _IF_RD_stage[RDEST_ADDR_RD] = _instruction.range(11, 8);
    _IF_RD_stage[RSRC_ADDR_RD] = _instruction.range(3, 0);
    _IF_RD_stage[IMMEDIATE_RD] = _instruction.range(7, 0);

    // Check Op Code
    switch(_instruction.range(15, 12).to_uint()) {
        case 0x0:
            // Check Extended Op Code (Arithmetic/Logic  Instructions)
            switch(_instruction.range(7, 4).to_uint()) {
                case 0x0: // NOP
                    _IF_RD_stage[ALU_OPCODE_RD] = (NOP);
                    _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                    break;
                case 0x1: // AND
                    _IF_RD_stage[ALU_OPCODE_RD] = (AND);
                    _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                    _IF_RD_stage[RF_WRITE_RD] = (0x1);
                    break;
                case 0x2: // OR
                    _IF_RD_stage[ALU_OPCODE_RD] = (OR);
                    _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                    _IF_RD_stage[RF_WRITE_RD] = (0x1);
                    break;
                case 0x3: // XOR
                    _IF_RD_stage[ALU_OPCODE_RD] = (XOR);
                    _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                    _IF_RD_stage[RF_WRITE_RD] = (0x1);
                    break;
                case 0x5: // ADD
                    _IF_RD_stage[ALU_OPCODE_RD] = (ADD);
                    _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                    _IF_RD_stage[RF_WRITE_RD] = (0x1);
                    break;
                case 0x9: // SUB
                    _IF_RD_stage[ALU_OPCODE_RD] = (SUB);
                    _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                    _IF_RD_stage[RF_WRITE_RD] = (0x1);
                    break;
                case 0xB: // CMP
                    _IF_RD_stage[ALU_OPCODE_RD] = (CMP);
                    _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                    break;
                case 0xD: // MOV
                    _IF_RD_stage[ALU_OPCODE_RD] = (MOV);
                    _IF_RD_stage[RF_WRITE_RD] = (0x1);
                    break;
            }
            break;
        case 0x1: // ANDI
            _IF_RD_stage[ALU_OPCODE_RD] = (ANDI);
            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            _IF_RD_stage[ALU_REG_2_RD] = (0x1);
            _IF_RD_stage[RF_WRITE_RD] = (0x1);
            break;
        case 0x2: // ORI
            _IF_RD_stage[ALU_OPCODE_RD] = (ORI);
            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            _IF_RD_stage[ALU_REG_2_RD] = (0x1);
            _IF_RD_stage[RF_WRITE_RD] = (0x1);
            break;
        case 0x3: // XORI
            _IF_RD_stage[ALU_OPCODE_RD] = (XORI);
            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            _IF_RD_stage[ALU_REG_2_RD] = (0x1);
            _IF_RD_stage[RF_WRITE_RD] = (0x1);
            break;
        case 0x4: 
                // Check Extended Op Code (Memory/Jump Instructions)
                switch(_instruction.range(7, 4).to_uint()) {
                    case 0x0: // LOAD
                        _IF_RD_stage[RESULT_SELECT_RD] = (0x2);
                        _IF_RD_stage[ALU_REG_1_RD] = (0x0);
                        _IF_RD_stage[ALU_REG_2_RD] = (0x0);
                        _IF_RD_stage[ALU_OPCODE_RD] = (LOAD);
                        _IF_RD_stage[RF_WRITE_RD] = (0x1);
                        break;
                    case 0x4: // STOR
                        _IF_RD_stage[DATA_RW_RD] = (0x01);
                        _IF_RD_stage[ALU_OPCODE_RD] = (STOR);
                        break;
                    case 0x8: // JAL
                        _IF_RD_stage[RESULT_SELECT_RD] = (0x01);
                        _IF_RD_stage[PC_SRC_RD] = (0x02);
                        _IF_RD_stage[ALU_OPCODE_RD] = (JAL);
                        _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        _IF_RD_stage[RF_WRITE_RD] = (0x1);
                        break;
                    case 0xC: // JCOND
                        if(CTRL_brnch_jmp_cond_check(_instruction.range(11, 8))) {
                            _IF_RD_stage[PC_SRC_RD] = (0x02);
                            _IF_RD_stage[ALU_OPCODE_RD] = (JCOND);
                            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        } else {
                            // NOP if condition is false
                            _IF_RD_stage[ALU_OPCODE_RD] = (NOP);
                            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        }
                        break;
                }
            break;
        case 0x5: // ADDI
            _IF_RD_stage[ALU_OPCODE_RD] = (ADDI);
            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            _IF_RD_stage[ALU_REG_2_RD] = (0x1);
            _IF_RD_stage[RF_WRITE_RD] = (0x1);
            break;
        case 0x8:
                // Check Extended Op Code (Shifting Instructions)
                switch(_instruction.range(7, 4).to_uint()) {
                    case 0x0: // LSHI_1
                        _IF_RD_stage[ALU_OPCODE_RD] = (LSHI_1);
                        _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        _IF_RD_stage[ALU_REG_2_RD] = (0x1);
                        _IF_RD_stage[RF_WRITE_RD] = (0x1);
                        break;
                    case 0x1: // LSHI_2
                        _IF_RD_stage[ALU_OPCODE_RD] = (LSHI_2);
                        _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        _IF_RD_stage[ALU_REG_2_RD] = (0x1);
                        _IF_RD_stage[RF_WRITE_RD] = (0x1);
                        break;
                    case 0x2: // ASHI_1
                        _IF_RD_stage[ALU_OPCODE_RD] = (ASHI_1);
                        _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        _IF_RD_stage[ALU_REG_2_RD] = (0x1);
                        _IF_RD_stage[RF_WRITE_RD] = (0x1);
                        break;
                    case 0x3: // ASHI_2
                        _IF_RD_stage[ALU_OPCODE_RD] = (ASHI_2);
                        _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        _IF_RD_stage[ALU_REG_2_RD] = (0x1);
                        _IF_RD_stage[RF_WRITE_RD] = (0x1);
                        break;
                    case 0x4: // LSH
                        _IF_RD_stage[ALU_OPCODE_RD] = (LSH);
                        _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        _IF_RD_stage[RF_WRITE_RD] = (0x1);
                        break;
                    case 0x6: // ASH
                        _IF_RD_stage[ALU_OPCODE_RD] = (ASH);
                        _IF_RD_stage[ALU_REG_1_RD] = (0x1);
                        _IF_RD_stage[RF_WRITE_RD] = (0x1);
                        break;
                }
            break;
        case 0x9: // SUBI
            _IF_RD_stage[ALU_OPCODE_RD] = (SUBI);
            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            _IF_RD_stage[ALU_REG_2_RD] = (0x1);
            _IF_RD_stage[RF_WRITE_RD] = (0x1);
            break;
        case 0xB: // CMPI
            _IF_RD_stage[ALU_OPCODE_RD] = (CMPI);
            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            _IF_RD_stage[ALU_REG_2_RD] = (0x1);
            break;
        case 0xC: // BCOND
            if(CTRL_brnch_jmp_cond_check(_instruction.range(11, 8))) {
                _IF_RD_stage[PC_SRC_RD] = (0x01);
                _IF_RD_stage[ALU_OPCODE_RD] = (BCOND);
                _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            } else {
                // NOP if condition is false
                _IF_RD_stage[ALU_OPCODE_RD] = (NOP);
                _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            }
            break;
        case 0xD: // MOVI
            _IF_RD_stage[ALU_OPCODE_RD] = (MOVI);
            _IF_RD_stage[ALU_REG_2_RD] = (0x1);
            _IF_RD_stage[RF_WRITE_RD] = (0x1);
            break;
        case 0xF: // LUI
            _IF_RD_stage[ALU_OPCODE_RD] = (LUI);
            _IF_RD_stage[ALU_REG_1_RD] = (0x1);
            _IF_RD_stage[ALU_REG_2_RD] = (0x1);
            _IF_RD_stage[RF_WRITE_RD] = (0x1);
            break;
    }
}

void CTRL::CTRL_proc() {
    while(true) {
        wait(); // Wait for positive edge
        // IF/RD Stage
        _RD_EXE_stage[RF_WRITE_EXE].write(_IF_RD_stage[RF_WRITE_RD]); 
        _RD_EXE_stage[RESULT_SELECT_EXE].write(_IF_RD_stage[RESULT_SELECT_RD]);
        _RD_EXE_stage[DATA_RW_EXE].write(_IF_RD_stage[DATA_RW_RD]);
        _RD_EXE_stage[PC_SRC_EXE].write(_IF_RD_stage[PC_SRC_RD]);
        _RD_EXE_stage[ALU_OPCODE_EXE].write(_IF_RD_stage[ALU_OPCODE_RD]);
        _RD_EXE_stage[ALU_REG_1_EXE].write(_IF_RD_stage[ALU_REG_1_RD]);
        _RD_EXE_stage[ALU_REG_2_EXE].write(_IF_RD_stage[ALU_REG_2_RD]);
        _RD_EXE_stage[PCP2_EXE].write(_IF_RD_stage[PCP2_RD]);
        _RD_EXE_stage[RDEST_ADDR_EXE].write(_IF_RD_stage[RDEST_ADDR_RD]);
        _RD_EXE_stage[IMMEDIATE_EXE].write(_IF_RD_stage[IMMEDIATE_RD]);
        _RD_EXE_stage[RDEST_DATA_EXE].write(rdest_data_in.read());
        _RD_EXE_stage[RSRC_DATA_EXE].write(rsrc_data_in.read());
        rdest_addr_rd.write(_IF_RD_stage[RDEST_ADDR_RD].read().to_uint()); 
        rsrc_addr.write(_IF_RD_stage[RSRC_ADDR_RD].read().to_uint());
        // RD/EXE Stage
        _EXE_MEM_stage[RF_WRITE_MEM].write(_RD_EXE_stage[RF_WRITE_EXE].read());
        _EXE_MEM_stage[RDEST_ADDR_MEM].write(_RD_EXE_stage[RDEST_ADDR_EXE].read());
        _EXE_MEM_stage[RESULT_SELECT_MEM].write(_RD_EXE_stage[RESULT_SELECT_EXE].read());
        _EXE_MEM_stage[DATA_RW_MEM].write(_RD_EXE_stage[DATA_RW_EXE].read());
        _EXE_MEM_stage[PCP2_MEM].write(_RD_EXE_stage[PCP2_EXE].read());
        _EXE_MEM_stage[RDEST_DATA_MEM].write(_RD_EXE_stage[RDEST_DATA_EXE].read());
        _EXE_MEM_stage[ALU_RES_MEM].write(alu_result_exe.read());
        CTRL_ALU_REG_1.write(_RD_EXE_stage[ALU_REG_1_EXE].read().to_uint());
        CTRL_ALU_REG_2.write(_RD_EXE_stage[ALU_REG_2_EXE].read().to_uint());
        CTRL_ALU_OPCODE.write(_RD_EXE_stage[ALU_OPCODE_EXE].read());
        CTRL_PC_SRC.write(_RD_EXE_stage[PC_SRC_EXE].read());
        jmp_tgt.write(_RD_EXE_stage[RSRC_DATA_EXE].read());
        rdest_data_out.write(_RD_EXE_stage[RDEST_DATA_EXE].read());
        rsrc_data_out.write(_RD_EXE_stage[RSRC_DATA_EXE].read());
        immediate.write(_RD_EXE_stage[IMMEDIATE_EXE].read());
        // EXE/MEM Stage
        _MEM_WB_stage[RF_WRITE_WB].write(_EXE_MEM_stage[RF_WRITE_MEM].read());
        _MEM_WB_stage[RDEST_ADDRESS_WB].write(_EXE_MEM_stage[RDEST_ADDR_MEM].read());
        _MEM_WB_stage[RESULT_SELECT_WB].write(_EXE_MEM_stage[RESULT_SELECT_MEM].read());
        _MEM_WB_stage[PCP2_WB].write(_EXE_MEM_stage[PCP2_MEM].read());
        _MEM_WB_stage[ALU_RES_WB].write(_EXE_MEM_stage[ALU_RES_MEM].read());
        _MEM_WB_stage[DATA_OUT_WB].write(data_dm.read());
        CTRL_DM_RW.write(_EXE_MEM_stage[DATA_RW_MEM].read().to_uint());
        alu_result_mem.write(_EXE_MEM_stage[ALU_RES_MEM].read());
        data_in.write(_EXE_MEM_stage[RDEST_DATA_MEM].read());
        // MEM/WB Stage
        CTRL_RF_WRITE.write(_MEM_WB_stage[RF_WRITE_WB].read().to_uint());
        CTRL_RESULT_SELECT.write(_MEM_WB_stage[RESULT_SELECT_WB].read());
        rdest_addr_wb.write(_MEM_WB_stage[RDEST_ADDRESS_WB].read());
        pc_next_wb.write(_MEM_WB_stage[PCP2_WB].read());
        alu_result_wb.write(_MEM_WB_stage[ALU_RES_WB].read());
        data_wb.write(_MEM_WB_stage[DATA_OUT_WB].read());
    }
}

bool CTRL::CTRL_brnch_jmp_cond_check(sc_bv<4> cond) {
    _flags = flags.read();
    switch(cond.to_uint()) {
        case EQ:
            // Z=1?
            if(_flags[3]) {
                return true;
            }
            return false;
        case NE:
            // Z=0?
            if(!(_flags[3])) {
                return true;
            }
            return false;
        case GE:
            // Z=1 or N=1?
            if(_flags[3] || _flags[2]) {
                return true;
            }
            return false;
        case CS:
            // C=1?
            if(_flags[1]) {
                return true;
            }
            return false;
        case CC:
            // C=0?
            if(!(_flags[1])) {
                return true;
            }
            return false;
        case GT:
            // N=1?
            if(_flags[2]) {
                return true;
            }
            return false;
        case LE:
            // N=0?
            if(!(_flags[2])) {
                return true;
            }
            return false;
        case FS:
            // F=1?
            if(_flags[0]) {
                return true;
            }
            return false;
        case FC:
            // F=0?
            if(!(_flags[0])) {
                return true;
            }
            return false;
        case LT:
            // N=0 and Z=0?
            if(!(_flags[2]) && !(_flags[3])) {
                return true;
            }
            return false;
    }
}
