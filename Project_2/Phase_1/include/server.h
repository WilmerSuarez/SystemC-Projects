// ============== ROBOT NAVIGATION ============== //
// 
// File : server.h
// This module monitors the robots and tells them 
// what to do depending on the robots positions
// and thier sensors.
//
// ============================================== //
#ifndef __SERVER_H__
#define __SERVER_H__
#include "defs.h"

/* Robot definitions */
#define STOP        2
#define RESTART     4

/* Server definitions */
#define OK                  0
#define START               1
#define STOP                2

/* Environment Packet Defnitions */
#define _s_CROSSING 1
#define _s_OBSTACLE 2
#define _s_RESTART  4

class server : public sc_module {
    public:
    // ----- PORTS ----- //
    sc_in_clk clk;
    sc_in <sc_bv<3> > packet_fromR{"PACKET_FROMR"};        // Packet from Robot ("Environment")
    sc_out <sc_bv<3> > packet_toR{"PACKET_TOR"};           // Packet going to Robot ("Environment")    
    sc_out <bool> packetValidS{"PACKET_VALIDS"};           // Packet Valid signal for Robot 

    // ----- CONSTRUCTOR ----- //
    SC_HAS_PROCESS(server);
        server(sc_module_name name, const std::vector<uint> robotPath) : 
        sc_module(name),
        _robotPath(robotPath) {

            SC_THREAD(server_rx);
                dont_initialize();
                sensitive << packet_fromR;

            SC_CTHREAD(server_update, clk.pos());

            SC_THREAD(server_tx);
                dont_initialize();
                sensitive << _s_tx;

            /* Initialize Output Ports */
            packetValidS.initialize(0);
            packet_toR.initialize(0);

            /* Grid map coordinate Initialization */
            map[0].LL.x = 0;
            map[0].LL.y = 0;
            map[0].UR.x = GRID_SIZE_X;
            map[0].UR.y = GRID_SIZE_Y;
            for(unsigned i = 1; i < MAX_GRID_INDEX; ++i) {
                map[i].LL.x += (map[i - 1].LL.x + GRID_SIZE_X);
                map[i].UR.x += (map[i - 1].UR.x + GRID_SIZE_X);
                map[i].UR.y = map[i - 1].UR.y;
            }

            /* Next Grid Initialization */
            robotNextGrid = {1, 1, 1, 1};

            /* RDS Table Initialization */
            for(unsigned i = 0; i < ROBOT_NUM; ++i) {
                RDS[i] = { _robotPath[0], _robotPath[robotNextGrid[i]], IDLE };
            }
            
            /*printf("PATH:\n");
            for(unsigned i = 0; i < 5; ++i) {
                printf("Path %d: %d\n", i+1, _robotPath[i]);
            }
            printf("MAP:\n");
            for(unsigned i = 0; i < MAX_GRID_INDEX; ++i) {
                printf("Grid %d: LL: x:%d y:%d\tUR: x:%d y:%d\n", i+1, map[i].LL.x, map[i].LL.y, map[i].UR.x, map[i].UR.y);
            }
            printf("TABLE:\n");
            printf("RI\tCG\tNG\tSTATUS\n");
            for(unsigned i = 0; i < ROBOT_NUM; ++i) {
                cout << i+1 << "\t" << RDS[i].CG << "\t" << RDS[i].NG << "\t" << RDS[i].STATUS << endl;
            }*/
        }
    private:
        // ----- METHODS ----- //
        void server_rx(); 
        void server_update();
        void server_tx();

        // ----- INTERNAL VARIABLES ----- //
        sc_bv<3> _packet_toR;      // Holds the current outgoing packet to the robot
        sc_bv<3> _packet_fromR;    // Holds incoming packet from robot
        sc_event _s_tx;            // Event triggered when server is ready to transmit packet  
        
        /* Robot path */
        const std::vector<uint> _robotPath;
        /* Holds index of next grid for all robots */
        std::vector<uint> robotNextGrid; 
};

#endif // __SERVER_H__
