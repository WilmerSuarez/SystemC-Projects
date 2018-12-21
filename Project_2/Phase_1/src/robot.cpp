// ============== ROBOT NAVIGATION ============== //
// 
// File : robot.cpp
// This module models the navigating Robots.
// The Robots serve as a communication point
// between the Server and the "Environment".
//
// ============================================== //
#include "robot.h"

/*
    Reads and stores data packets from
    Server or "Environment"
*/
void robot::robot_proc_rx() {
    _packet_validS.write(packet_validS.read());
    _packet_validE.write(packet_validE.read());
    while(true) {
        wait();
        if(_packet_validS.read()) {
            /* Store packet from Server */
            _packet_validS.write(0);
            _packet_fromS = packet_fromS.read();
        } else if(_packet_validE.read()) {
            /* Store packet from Environment */
            _packet_validE.write(0);
            _packet_fromE = packet_fromE.read();
        }
        _r_tx.notify();
    }
}

/*
    Sends data packets to 
    Server or "Environment"
*/
void robot::robot_proc_tx() {
    while(true) {
        wait();
        if(!_packet_validS.read()) {
            /* Transmit: Server -> Environment */
            packet_toE.write(_packet_fromS);
        } else if(!_packet_validE.read()) {
            /* Transmit: Environment -> Server */
            packet_toS.write(_packet_fromE);
        }
    }
}
