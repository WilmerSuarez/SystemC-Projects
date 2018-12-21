// ============== ROBOT NAVIGATION ============== //
// 
// File : environment.h
// This module emulates the robot's motors, GPS, 
// sensors, and human traffic. 
//
// ============================================== //
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__
#include "systemc.h"
#include "defs.h"

/* Environment definitions */
#define CROSSING    0
#define OBSTACLE    1
#define CLEARED     2

/* Server Packet definitions */
#define _e_OK       1
#define _e_START    2
#define _e_STOP     4

class environment : public sc_module {
    public:
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_in <sc_bv<3> > packet_fromS{"PACKET_FROMS"};        // Packet from Server
    sc_out <sc_bv<3> > packet_toS{"PACKET_TOS"};           // Packet going to Server 
    sc_out <bool> packetValidE{"PACKET_VALIDE"};           // Packet Valid signal for Robot                  

    // ----- CONSTRUCTOR ----- //
    SC_HAS_PROCESS(environment);
        environment(sc_module_name name) : 
        sc_module(name) {

            SC_THREAD(environment_rx);
                dont_initialize();
                sensitive << packet_fromS;

            SC_CTHREAD(environment_update, clk.pos());

            SC_THREAD(environment_tx);
                dont_initialize();
                sensitive << _e_tx;

            /* Initialize Output Ports */
            packetValidE.initialize(0);
            packet_toS.initialize(0);

            /* Robot Position Map Initialization */
            for(unsigned i = 0; i < ROBOT_NUM; ++i) {
                robotMap[i] = { 0, RDS[i].CG , IDLE };
            }

            /* Obstacle Map Initialization*/
            for(unsigned i = 0; i < MOVING_OBSTACLE_NUM; ++i) {
                obstacleMap[i] = { 4, 4 };
            }

            /*printf("ROBOT POSITION MAP:\n");
            for(unsigned i = 0; i < ROBOT_NUM; ++i) {
                printf("X: %d Current Grid: %d", robotMap[0]._r_x, robotMap[0].gridNum);
            }*/

            /*printf("MAP:\n");
            for(unsigned i = 0; i < MAX_GRID_INDEX; ++i) {
                printf("Grid %d: LL: x:%d y:%d\tUR: x:%d y:%d\n", i+1, map[i].LL.x, map[i].LL.y, map[i].UR.x, map[i].UR.y);
            }*/
        }
    private:
        // ----- METHODS ----- //
        void environment_rx(); 
        void environment_update();
        void environment_tx();

        // ----- INTERNAL VARIABLES ----- //0
        sc_bv<3> _packet_toS;      // Holds the current outgoing packet to the server
        sc_bv<3> _packet_fromS;    // Holds incoming packet from Server
        sc_event _e_tx;            // Event triggered when environment is ready to transmit packet  

        /* 
            Robot position Table
        */
        struct robotMap {
            uint _r_x;              // X position of Robot 
            uint gridNum;           // Robot Grid Number
            std::string STATUS;     // Robot Status
        } robotMap[ROBOT_NUM];

        /* 
            Obstacle position Table
        */
        struct obstacleMap {
            uint _o_x;              // X position of Obstacle
            uint gridNum;           // Obstacle Grid Number
        } obstacleMap[MOVING_OBSTACLE_NUM];
    
};

#endif // __ENVIRONMENT_H__
