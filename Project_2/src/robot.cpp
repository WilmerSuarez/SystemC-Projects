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
    the Server
*/
void robot::robot_proc_server_rx() {
    while(true) {
        wait();
        /* Store packet from Server */
        _packet_fromS = packet_fromS.read();
        _r_e_tx.notify();
    }
}

/*
    Sends Server data packets to 
    the Environment
*/
void robot::robot_proc_env_tx() {
    while(true) {
        wait(_r_e_tx);
        packet_toE.write(_packet_fromS);
    }
}

/*
    Reads and stores data packets from
    the Environment
*/
void robot::robot_proc_env_rx() {
    while(true) {
        wait();
        /* Store packet from Environment */
        _packet_fromE = packet_fromE.read();
        _r_s_tx.notify();
    }
}

/*
    Sends Environment data packets to 
    the Server
*/
void robot::robot_proc_server_tx() {
    while(true) {
        wait(_r_s_tx);
        packet_toS.write(_packet_fromE);
    }
}
