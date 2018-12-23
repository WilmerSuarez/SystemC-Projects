// ============== ROBOT NAVIGATION ============== //
// 
// File : server.cpp
// This module monitors the robots and tells them 
// what to do depending on the robots positions
// and their sensors.
//
// ============================================== //
#include "server.h"

/*
    Receive the incoming packet from the Robot.
*/
void server::server_rx() {
    while(true) {
        wait();
        /* Store the packet received by the robots */
        for(uint r = 0; r < ROBOT_NUM; ++r) {
            _packet_fromR[r] = packet_fromR[r].read();
        }
        cout << "@: " << sc_time_stamp() << "\n";
        printf("RX: Server: from Robot\n");
        for(int i = 0; i < ROBOT_NUM; ++i) {
            cout << "RX: _packet_fromR" << i+1 << ":" << _packet_fromR[i] << endl;
        }
    }
}

/* Updates the database with respect to the Robot packet received */
void server::update_robot(sc_bv<3> robotPacket, uint r_num) {
    /*
        Server Packet -> to Environment:
            bit_0: RESTART/CONTINUE - Next Grid is clear (OK to continue moving)
            bit_1: START - From beginning (IDLE)
            bit_2: STOP - Avoid Collision or Not allowed through node yet
        Environment Packet -> to Server:
            bit_0: CROSSING - Robot is crossing boundary - 0.5m away from a boundary.
            bit_1: STOP/OBSTACLE - Obstacle detected. 3m away from an obstacle.
            bit_2: RESTART/CLEARED - Obstacle clear       
    */
    if(robotPacket.to_uint() & OBSTACLE) {
        /* Robot has stopped due to an obstacle in the way */
        RSDS[r_num].NS = STOPPED;
        RSDS[r_num].speed = 0;
        _packet_toR[r_num][_s_bit_CONTINUE] = 0;
        cout << "@: " << sc_time_stamp() << endl;
        cout << "Obstacle in the way: Robot " << r_num+1 <<  endl;
        cout << "Status: " << RSDS[r_num].NS << endl;
        cout << "Speed: " << RSDS[r_num].speed << endl;
        return;
    } else if(robotPacket.to_uint() & CLEARED) {
        /* Obstacle obstructing robot has moved */
        RSDS[r_num].NS = MOVING;
        if(RSDS[r_num].speed < ROBOT_SPEED_MAX) {
            RSDS[r_num].speed += ROBOT_STEP_SIZE;
        }
        cout << "@: " << sc_time_stamp() << endl;
        cout << "Obstacle Clear: Robot " << r_num+1 << " Moving: Speed increased" << endl;
        cout << "Status: " << RSDS[r_num].NS << endl;
        cout << "Speed: " << RSDS[r_num].speed << endl;
    } else if(robotPacket.to_uint() & CROSSING) { 
        uint s_flag = 0; // Stopped or not?
        
        /* Check if other robot is in next grid */
        for(uint r = 0; r < ROBOT_NUM; ++r) {
            if(RSDS[r_num].NG.front() == RSDS[r].CG.front()) {
                /* Send STOP signal to avoid collision */
                _packet_toR[r_num][_s_bit_STOP] = 1;
                _packet_toR[r_num][_s_bit_CONTINUE] = 0;
                RSDS[r_num].NS = STOPPED;
                RSDS[r_num].speed = 0;
                s_flag = 1;
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Collision Imminent: Robot " << r_num+1 << " Stopped" << endl;
                break;
            } else {    
                /* No collision at the moment - Continue */
                _packet_toR[r_num][_s_bit_STOP] = 0;
                _packet_toR[r_num][_s_bit_CONTINUE] = 1;
                s_flag = 0;
            }
        }

        if(_packet_toR[r_num][_s_bit_STOP] == 0) {
            cout << "No collision: CONTINUE" << endl;
        }
        cout << "Status: " << RSDS[r_num].NS << endl;
        cout << "Speed: " << RSDS[r_num].speed << endl;
        return;
    } 

    /* Hold Next Node of current Robot */
    struct NO *n = &nodes[RSDS[r_num].NN.front()];
    /* Check node scheduling */
    /* If current robot is first at its NN */
    if(n->first == (r_num+1)) {
        if(RSDS[r_num].NG.front() == n->gridNum) {
            /* Clear spot if node queue */
            n->first = 0;
            /* Update current robot next node */
            RSDS[r_num].NN.pop_front();
            cout << "@: " << sc_time_stamp() << endl;
            cout << "FIRST" << endl;
            cout << "Node Updated for Robot: " << r_num+1 << " NN: " << RSDS[r_num].NN.front() << endl; 
        }
    } else if(n->second == (r_num+1)) {
        /* If current robot is second at its NN */
        if(RSDS[r_num].NG.front() == n->gridNum) {
            if(n->first) {
                /* Stop, wait for first robot to go through */
                _packet_toR[r_num][_s_bit_STOP] = 1;
                _packet_toR[r_num][_s_bit_CONTINUE] = 0;
                RSDS[r_num].NS = STOPPED;
                RSDS[r_num].speed = 0;
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Robot: " << r_num+1 << " stopped, not it's turn: NN: " << RSDS[r_num].NN.front() << endl; 
                cout << "SECOND" << endl;
                cout << "Status: " << RSDS[r_num].NS << endl;
                cout << "Speed: " << RSDS[r_num].speed << endl;
            } else if(!n->first) {
                /* Clear spot in node queue */
                n->second = 0;
                /* Update current robot next node */
                RSDS[r_num].NN.pop_front();
                /* Change status to MOVING if previously not */
                _packet_toR[r_num][_s_bit_STOP] = 0;
                _packet_toR[r_num][_s_bit_CONTINUE] = 1;
                RSDS[r_num].NS = MOVING;
                if(RSDS[r_num].speed < ROBOT_SPEED_MAX) {
                    RSDS[r_num].speed += ROBOT_STEP_SIZE;
                }
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Queue val: " << n->second;
                cout << "Node Updated for Robot: " << r_num+1 << " New NN: " << RSDS[r_num].NN.front() << endl; 
                cout << "SECOND" << endl;
                cout << "Status: " << RSDS[r_num].NS << endl;
                cout << "Speed: " << RSDS[r_num].speed << endl;
            }
        }
    } else if(n->third == (r_num+1)) {
        /* If current robot is third at its NN */
        if(RSDS[r_num].NG.front() == n->gridNum) {
            if(n->second) {
                /* Stop, wait for second robot to go through */
                _packet_toR[r_num][_s_bit_STOP] = 1;
                _packet_toR[r_num][_s_bit_CONTINUE] = 0;
                RSDS[r_num].NS = STOPPED;
                RSDS[r_num].speed = 0;
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Robot: " << r_num+1 << " stopped, not it's turn: NN: " << RSDS[r_num].NN.front() << endl; 
                cout << "THIRD" << endl;
                cout << "Status: " << RSDS[r_num].NS << endl;
                cout << "Speed: " << RSDS[r_num].speed << endl;
            } else if(!n->second) {
                /* Clear spot in node queue */
                n->third = 0;
                /* Update current robot next node */
                RSDS[r_num].NN.pop_front();
                /* Change status to MOVING if previously not */
                _packet_toR[r_num][_s_bit_STOP] = 0;
                _packet_toR[r_num][_s_bit_CONTINUE] = 1;
                RSDS[r_num].NS = MOVING;
                if(RSDS[r_num].speed < ROBOT_SPEED_MAX) {
                    RSDS[r_num].speed += ROBOT_STEP_SIZE;
                }
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Queue val: " << n->third;
                cout << "Node Updated for Robot: " << r_num+1 << " New NN: " << RSDS[r_num].NN.front() << endl; 
                cout << "THIRD" << endl;
                cout << "Status: " << RSDS[r_num].NS << endl;
                cout << "Speed: " << RSDS[r_num].speed << endl;
            }
        }
    } else if(n->fourth == (r_num+1)) {
        /* If current robot is fourth at its NN */
        if(RSDS[r_num].NG.front() == n->gridNum) {
            if(n->third) {
                /* Stop, wait for second third to go through */
                _packet_toR[r_num][_s_bit_STOP] = 1;
                _packet_toR[r_num][_s_bit_CONTINUE] = 0;
                RSDS[r_num].NS = STOPPED;
                RSDS[r_num].speed = 0;
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Robot: " << r_num+1 << " stopped, not it's turn: NN: " << RSDS[r_num].NN.front() << endl; 
                cout << "FOURTH" << endl;
                cout << "Status: " << RSDS[r_num].NS << endl;
                cout << "Speed: " << RSDS[r_num].speed << endl;
            } else if(!n->third) {
                /* Clear spot in node queue */
                n->fourth = 0;
                /* Update current robot next node */
                RSDS[r_num].NN.pop_front();
                /* Change status to MOVING if previously not */
                _packet_toR[r_num][_s_bit_STOP] = 0;
                _packet_toR[r_num][_s_bit_CONTINUE] = 1;
                RSDS[r_num].NS = MOVING;
                if(RSDS[r_num].speed < ROBOT_SPEED_MAX) {
                    RSDS[r_num].speed += ROBOT_STEP_SIZE;
                }
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Queue val: " << n->fourth;
                cout << "Node Updated for Robot: " << r_num+1 << " New NN: " << RSDS[r_num].NN.front() << endl; 
                cout << "FOURTH" << endl;
                cout << "Status: " << RSDS[r_num].NS << endl;
                cout << "Speed: " << RSDS[r_num].speed << endl; 
            }
        }
    }
}

/*
    Updates internal Data Structure 
    that stores Robot information and status.
*/
void server::server_update() {
    while(true) {
        wait();
        /* If robot is idle, start it (at its appropriate time) */
        _t = sc_time_stamp();
        for(unsigned r = 0; r < ROBOT_NUM; ++r) {
            if(_robot_S_T[r] == _t) {
                RSDS[r].NS = MOVING;
                /* Send START signal to corresponding Robot */
                _packet_toR[r][_s_bit_START] = 1;
                if(RSDS[r].speed < ROBOT_SPEED_MAX) {
                    RSDS[r].speed += ROBOT_STEP_SIZE;
                }
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Robot " << r+1 << " IDLE --> MOVING" << endl;
                cout << "Speed: " << RSDS[r].speed << endl;
            }
        }
        
        /* Update robots if they have been started */
        for(unsigned r = 0; r < ROBOT_NUM; ++r) {
            if(RSDS[r].NS != IDLE) {
                cout << "@: " << sc_time_stamp() << endl;
                cout << "Updating Robot" << r+1 << ": Packet: " << _packet_fromR[r] << endl;
                update_robot(_packet_fromR[r], r);
            }     
        }

        /* 
            Finished processing packet from Robots.
            Transmit reply.
        */
        cout << "@: " << sc_time_stamp() << "\n"; 
        printf("Sever: Updated\n");
        _s_tx.notify();  
    }
}

/*
    Transmit the updated packets to the Robots
*/
void server::server_tx() {
    while(true) {
        wait();
        /* Transmit packets to Robots */
        for(int i = 0; i < ROBOT_NUM; ++i) {
            packet_toR[i].write(_packet_toR[i]);
        }
        cout << "@: " << sc_time_stamp() << "\n";
        printf("TX: Server: to Robot\n");
        for(int i = 0; i < ROBOT_NUM; ++i) {
            cout << "TX: _packet_toR" << i+1 << ":" << _packet_toR[i] << endl;
        }
    }
}
