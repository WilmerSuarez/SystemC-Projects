// ============== ROBOT NAVIGATION ============== //
// 
// File : environment.cpp
// This module emulates the robot's motors, GPS, 
// sensors, and human traffic. 
//
// ============================================== //
#include "environment.h"

/*
    Receive the incoming packet from the Robot.
    Read which robot is currently being processed.
*/
void environment::environment_rx() {
    while(true) {
        wait();
        /* Store the packet received by the Server */
        _packet_fromS = packet_fromS.read();
    }
}

/*
    Update the robot & obstacle positions.
    Determine if the robot is corssing a boarder,
    about to collide with obstacle, or if it is clear
    of an obstacle.
*/
void environment::environment_update() {
    while(true) {
        wait();

        switch(_packet_fromS.to_uint()) {
            case _e_OK: /* OK to move to the next Grid */
                robotMap[0].STATUS = MOVING;
                break;
            case _e_START: /* Robot is IDLE & Server sent START Signal */
                /* Start the Robot */
                robotMap[0].STATUS = MOVING;
                break;
            case _e_STOP: /* Server sent STOP signal */
                /* Stop the Robot */
                robotMap[0].STATUS = STOPPED;
            break;
        }
        
        /* Update Position of All robots */
        for(unsigned i = 0; i < ROBOT_NUM; ++i) {
            /* If the robot is not stopped by the Server, continue */
            if(robotMap[i].STATUS == STOPPED) {
                continue;
            } else {
                robotMap[i]._r_x += ROBOT_STEP_SIZE;
            }
        }
        /* Update all obstacles */
        for(unsigned i = 0; i < MOVING_OBSTACLE_NUM; ++i) {
            /* Remain Stationary for now */
            //obstacleMap[i]._o_x += OBSTACLE_STEP_SIZE;
        }
        /* Compare robot distance from Boundary */
        for(unsigned i = 0; i < ROBOT_NUM; ++i) {
            if(robotMap[i]._r_x >= (map[robotMap[i].gridNum + 1].LL.x - 0.5)) {
                /* If close to boundary, send signal to Server */
                _packet_toS[CROSSING] = 1;
            }
        }
        /* Compare all robots distance from obstacles */
        for(unsigned i = 0; i < ROBOT_NUM; ++i) {
            for(unsigned j = 0; j < MOVING_OBSTACLE_NUM; ++j) {
                if(robotMap[i]._r_x >= obstacleMap[j]._o_x - 3) {
                    _packet_toS[OBSTACLE] = 1;
                    robotMap[i].STATUS = STOPPED;
                } else {
                    _packet_toS[CLEARED] = 1;
                }
            }
        }
        /* 
            Finished processing packet from Server. 
            Transmit reply.
        */
        _e_tx.notify();
    }
}

/*
    Transmit the packet 
*/
void environment::environment_tx() {
    /* Transmit packet to Robot */
    packet_toS.write(_packet_toS);
    packetValidE.write(1);
}
