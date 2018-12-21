// ============ MINI RISC PROCESSOR ============ //
// 
// File : IM.cpp
// This module stores the instructions of the 
// program currently executing on the Processor.
//
// ============================================= //
#include "IM.h"

/*
*   This process updates the Program Counter
*   every clock cycle and sends the address to 
*   the Instruction Memory. The IM then outputs
*   the corresponding instruction.
*/
template<typename T, size_t M_SIZE>
void IM<T, M_SIZE>::IM_proc() {
    while(true) {

        wait(); // Wait for event (posedge clk)

        // Increment PC
        _pc_next = (_im_address.read() + 1);

        // Choose what to update the Program Counter with
        switch(CTRL_PC_SRC.read().to_uint()) {
            case PCP2:
                    _im_address.write(_pc_next);
                break;
            case BRANCH:
                    _branch_disp.write(branch_disp.read());
                    _im_address.write(_im_address.read() + _branch_disp.read());
                break;
            case JUMP:
                    _im_address.write(jmp_target.read());
                break;
        }

        // Output the address of the next instruction
        pc_next.write(_pc_next);

        // Output instruction at location indexed by _im_address
        instruction.write(_instruction_memory[_im_address.read()]);
    }
}         
