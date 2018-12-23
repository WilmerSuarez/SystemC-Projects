// ============ MINI RISC PROCESSOR ============ //
// 
// File : ALU.cpp
// This module performs the arithmetic and
// logic operations needed by the program 
// currently executing on the processor.
//
// ============================================= //
#include "ALU.h"

void ALU::ALU_proc() {
    // ALU operand 1
    if(CTRL_ALU_REG_1.read()) {
        _reg1_data = rdest_data.read();        
    } else {
        _reg1_data = 0;
    }

    // ALU operand 2
    if(CTRL_ALU_REG_2.read()) {
        _immediate_extended_logic = immediate_in;
        _immediate_extended_arithmetic = immediate_in;
    } else {
        _reg2_data = rsrc_data.read();
    }

    // ALU operations 
    switch(CTRL_ALU_OPCODE.read().to_uint()){
        case NOP:
        case OR:
        case ORI:
        case BCOND:
        case JCOND:
        case JAL:
            if(CTRL_ALU_REG_1.read() && CTRL_ALU_REG_2.read()) {
                _alu_result = _reg1_data | _immediate_extended_logic;
            } else if(CTRL_ALU_REG_1.read() && !CTRL_ALU_REG_2.read()){
                _alu_result = _reg1_data | _reg2_data;
            }
            break;
        case ADD:
        case ADDI:
        case MOV:
        case MOVI:
        case LOAD:
        case STOR:
            if(CTRL_ALU_REG_1.read() && CTRL_ALU_REG_2.read()) {
                // Test for carry/borrow (unsigned) (C Flag - 2nd bit)
                if((_immediate_extended_arithmetic > 0) && (_reg1_data > (__UINT16_MAX__ - _immediate_extended_arithmetic))) {
                    _psr[1] = "1";
                }
                // Test for overflow (signed) (F Flag - 1st bit)
                if((_immediate_extended_arithmetic > 0) && (_reg1_data > (__INT16_MAX__ - _immediate_extended_arithmetic))) {
                    _psr[0] = "1";
                }
                _alu_result = _reg1_data + _immediate_extended_arithmetic;
            } else if(CTRL_ALU_REG_1.read() && !CTRL_ALU_REG_2.read()){
                // Test for carry/borrow (unsigned) (C Flag - 2nd bit)
                if((_reg2_data > 0) && (_reg1_data > (__UINT16_MAX__ - _reg2_data))) {
                    _psr[1] = "1";
                }
                // Test for overflow (signed) (F Flag - 1st bit)
                if((_reg2_data > 0) && (_reg1_data > (__INT16_MAX__ - _reg2_data))) {
                    _psr[0] = "1";
                }
                _alu_result = _reg1_data + _reg2_data;
            } else if(!CTRL_ALU_REG_1.read() && CTRL_ALU_REG_2.read()) {
                _alu_result = _immediate_extended_arithmetic;
            } else {
                _alu_result = _reg2_data;
            }
            break;
        case SUB:
        case SUBI:
        case CMP:
        case CMPI:
            if(CTRL_ALU_REG_1.read() && CTRL_ALU_REG_2.read()) {
                // Test for carry/borrow (unsigned) (C Flag - 2nd bit)
                if((_immediate_extended_arithmetic < 0) && (_reg1_data > (__UINT16_MAX__ + _immediate_extended_arithmetic))) {
                    _psr[1] = "1";
                }
                // Test for overflow (signed) (F Flag - 1st bit)
                if((_immediate_extended_arithmetic < 0) && (_reg1_data > (__INT16_MAX__ + _immediate_extended_arithmetic))) {
                    _psr[0] = "1";
                }
                // Test N Flag (3rd bit)
                if(_reg1_data ^ _immediate_extended_logic) {
                    _psr[2] = "1";
                }
                _alu_result = _reg1_data - _immediate_extended_arithmetic;
                // Test for zero (Z Flag - 4th bit)
                if(_alu_result == 0) {
                    _psr[3] = "1";
                }
            } else if(CTRL_ALU_REG_1.read() && !CTRL_ALU_REG_2.read()){
                // Test for carry/borrow (unsigned) (C Flag - 2nd bit)
                if((_reg2_data < 0) && (_reg1_data > (__UINT16_MAX__ + _reg2_data))) {
                    _psr[1] = "1";
                }
                // Test for overflow (signed) (F Flag - 1st bit)
                if((_reg2_data < 0) && (_reg1_data > (__INT16_MAX__ + _reg2_data))) {
                    _psr[0] = "1";
                }
                // Test N Flag (3rd bit)
                if(_reg1_data ^ _reg2_data) {
                    _psr[2] = "1";
                }
                _alu_result = _reg1_data - _reg2_data;
                // Test for zero (Z Flag - 4th bit)
                if(_alu_result == 0) {
                    _psr[3] = "1";
                }
            }
            break;
        case AND:
        case ANDI:
            if(CTRL_ALU_REG_1.read() && CTRL_ALU_REG_2.read()) {
                _alu_result = _reg1_data & _immediate_extended_logic;
            } else if(CTRL_ALU_REG_1.read() && !CTRL_ALU_REG_2.read()){
                _alu_result = _reg1_data & _reg2_data;
            }
            break;
        case XOR:
        case XORI:
            if(CTRL_ALU_REG_1.read() && CTRL_ALU_REG_2.read()) {
                _alu_result = _reg1_data ^ _immediate_extended_logic;
            } else if(CTRL_ALU_REG_1.read() && !CTRL_ALU_REG_2.read()){
                _alu_result = _reg1_data ^ _reg2_data;
            }
            break;
        case LSH:
            _alu_result = (int) ((unsigned int)_reg1_data) << _reg2_data;
            break;
        case LSHI_1:
            _alu_result =  (int) ((unsigned int)_reg1_data) << _immediate_extended_logic.range(3, 0);
            break;
        case LSHI_2:
            _alu_result =  (int) ((unsigned int)_reg1_data) >> _immediate_extended_logic.range(3, 0);
            break;
        case ASH:
            _alu_result = _reg1_data << _reg2_data;
            break;
        case ASHI_1:
            _alu_result =  _reg1_data << _immediate_extended_logic.range(3, 0);
        case ASHI_2:
            _alu_result = _reg1_data >> _immediate_extended_logic.range(3, 0);
            break;
        case LUI:
            sc_uint<16> mask = 0x00FF;
            _alu_result = (_reg1_data & mask) | (_immediate_extended_logic.range(7, 0) << 8);
            break;
    }
    flags.write(_psr);
    alu_result.write(_alu_result);
}
