// ============ MINI RISC PROCESSOR ============ //
// 
// File : DM.cpp
// This module is the general purpose RAM. 
// Stores data for the executing program.
//
// ============================================= //
#include "DM.h"

template<typename T, size_t M_SIZE>
void DM<T, M_SIZE>::DM_proc() {
    while(true) {
        wait(); // Wait for event (posedge clk)

        // Write to data memory if write enable is asserted
        if(CTRL_DM_RW) {
            _dm_address.write(dm_addr.read());
            _data_memory[_dm_address.read()] = data_in.read();
        }

        // Read Data Memory
        //_dm_result.write(_data_memory[_dm_address.read()]);

        // Output DM read result - to be used in Write Back Stage
        //data_out.write(_dm_result.read());
        data_out.write(_data_memory[_dm_address.read()]);
    }
}

template<typename T, size_t M_SIZE>
void DM<T, M_SIZE>::final_result_proc() {
    // Decide Final Output
    switch(CTRL_RESULT_SELECT.read().to_uint()) {
        case _ALU_RESULT:
                _alu_result_mux.write(alu_result.read());
                final_result.write(_alu_result_mux.read());
            break;
        case JAL_LINK:
                _jal_link.write(pc_next.read());
                final_result.write(_jal_link.read());
            break;
        case DM_OUT:
                _dm_result_mux.write(dm_result.read());
                final_result.write(_dm_result_mux.read());
            break;
    }
}