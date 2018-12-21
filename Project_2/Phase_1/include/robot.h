// ============== ROBOT NAVIGATION ============== //
// 
// File : robot.h
// This module models the navigating Robots.
// The Robots serve as a communication point
// between the Server and the "Environment".
//
// ============================================== //
#ifndef __ROBOT_H__
#define __ROBOT_H__
#include "systemc.h"

class robot : public sc_module {
    public:
    // ----- PORTS ----- //
    /*
        Server Packet -> to Environment:
            bit_0: RESTART/CONTINUE - Next Grid is clear (OK to continue moving)
            bit_1: START - From beginning (IDLE)
            bit_2: STOP - Avoid Collision   
        Environment Packet -> to Server:
            bit_0: CROSSING - Robot is crossing boundary - 0.5m away from a boundary.
            bit_1: STOP/OBSTACLE - Obstacle detected. 3m away from an obstacle.
            bit_2: RESTART/CLEARED - Obstacle clear          
    */ 
    sc_in <bool> packet_validS{"PACKET_VALIDS"};           // Server Packet Valid?
    sc_in <bool> packet_validE{"PACKET_VALIDE"};           // Environment Packet Valid?
    sc_in <sc_bv<3> > packet_fromE{"PACKET_FROME"};        // Packet from Environment
    sc_in <sc_bv<3> > packet_fromS{"PACKET_FROMS"};        // Packet from Server
    sc_out <sc_bv<3> > packet_toE{"PACKET_TOE"};           // Packet going to Environment
    sc_out <sc_bv<3> > packet_toS{"PACKET_TOS"};           // Packet going to Server

    // ----- CONSTRUCTOR ----- //
    SC_HAS_PROCESS(robot);
    robot(sc_module_name name) :
    sc_module(name) {
        SC_THREAD(robot_proc_rx);
            dont_initialize();
            sensitive << packet_validS << packet_validE;  
        SC_THREAD(robot_proc_tx);
            dont_initialize();
            sensitive << _r_tx;  

        /* Initialize Output Ports */
        packet_toE.initialize(0);
        packet_toS.initialize(0);
    }

    private:
    // ----- METHODS ----- //
    void robot_proc_rx();    
    void robot_proc_tx();

    // ----- INTERNAL VARIABLES & SIGNALS ----- //
    sc_event _r_tx;                    // Event triggered when Robot is ready to Transmit
    sc_signal<bool> _packet_validS;    // Holds valid bit for Server Packet
    sc_signal<bool> _packet_validE;    // Holds valid bit for Environment Packet
    sc_bv<3> _packet_fromE;            // Stores packet received from Environment
    sc_bv<3> _packet_fromS;            // Stores packet received from Server
    sc_bv<3> _packet_toE;              // Stores packet to be sent to Environment
        
};

#endif // __ROBOT_H__
