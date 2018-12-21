// ============== ROBOT NAVIGATION ============== //
// 
// File : server.cpp
// This module monitors the robots and tells them 
// what to do depending on the robots positions
// and their sensors.
//
// ============================================== //
#include "defs.h"
#include "server.h"

/*
    Receive the incoming packet from the Robot.
    Read which robot is currently being processed.
*/
void server::server_rx() {
    while(true) {
        wait();
        /* Store the packet received by the robot */
        _packet_fromR = packet_fromR.read();
    }
}

/*
    Updates internal Data Structure 
    that stores Robot information.
*/
void server::server_update() {
    while(true) {
        wait();
        /* If robot is idle, start it */
        if(RDS[0].STATUS == IDLE) {
            _packet_toR[START] = 1;
            RDS[0].STATUS = MOVING;
        } else {
            switch(_packet_fromR.to_uint()) {
                case _s_CROSSING: /* Robot is about to cross a grid boundary - 0.5m away */
                    /* No robot-to-robot collision possible - Only one robot for now */
                    /* Robot moved to Next Grid */
                    RDS[0].CG = RDS[0].NG;
                    /* Update robots Next Grid in RDS */
                    if((robotNextGrid[0] + 1) < _robotPath.size()) {    
                        RDS[0].NG = _robotPath[++robotNextGrid[0]];
                    }
                    /* Send "OK to Cross" Signal */
                    _packet_toR[OK] = 1;
                    break;
                case _s_OBSTACLE: /* Robot is stopped - Obstacle in the way */ 
                    RDS[0].STATUS = STOPPED;
                    break;
                case _s_RESTART: /* Obstacle clear - Robot Moving */
                    RDS[0].STATUS = MOVING;
                    break;
            }
        }
        /* 
            Finished processing packet from Robot.
            Transmit reply.
        */
        _s_tx.notify();     
    }
}

/*
    Transmit the packet 
*/
void server::server_tx() {
    /* Transmit packet to Robot */
    packet_toR.write(_packet_toR);
    packetValidS.write(1);
}
