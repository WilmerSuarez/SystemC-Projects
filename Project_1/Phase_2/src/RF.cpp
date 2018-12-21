// ============ MINI RISC PROCESSOR ============ //
// 
// File : RF.h
// This module contains 16, 16-bit registers 
// used to store the data being manipulated 
// by the ALU. 
//
// ============================================= //
#include "RF.h"

/*
*   This Process Reads the two register File
*   Addresses and outputs the data to the ALU
*   on every rising edge of the clock.
*/
template<typename T>
void RF<T>::RF_proc_read() {
    while(true) {
        wait(); // Wait for event (posedge clk)
        
        // Output register contents at address' pointed to by rdest_addr & rsrc_addr
        _rdest_addr = rdest_addr.read();
        _rsrc_addr = rsrc_addr.read();
        rdest_data.write(_register_file[_rdest_addr] );
        rsrc_data.write(_register_file[_rsrc_addr]);
    }
}    

/*
*   This process updates a register on the 
*   Register File if the write enable signal
*   is received.
*/
template<typename T>
void RF<T>::RF_proc_write() {
    while(true) {
        wait(); // Wait for event (negedge clk)
        
        // Write to Write Back Register? 
        if(CTRL_RF_WRITE.read()) {
            // Update register pointed to by wb_reg address with data_in contents.
            _wb_reg_addr = wb_reg.read();
            _register_file[_wb_reg_addr] = data_in.read();
        }
       
    }
}  
