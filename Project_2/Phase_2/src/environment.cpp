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
*/
void environment::environment_rx() {
    while(true) {
        wait();
        /* Store the packet received by the Server */
        for(uint r = 0; r < ROBOT_NUM; ++r) {
            _packet_fromS[r] = packet_fromS[r].read();
        }
        cout << "@: " << sc_time_stamp() << "\n";
        printf("RX: Environment: from Robot<-Server\n");
        for(int i = 0; i < ROBOT_NUM; ++i) {
            cout << "RX: _packet_fromS" << i+1 << ":" << _packet_fromS[i] << endl;
        }
    }
}

/*
    Update Robot Positions
*/
void environment::update_robot_pos() {
    /*
        Server Packet -> to Environment:
            bit_0: RESTART/CONTINUE - Next Grid is clear (OK to continue moving)
            bit_1: START - From beginning (IDLE)
            bit_2: STOP - Avoid Collision - Not allowed through node yet
        Environment Packet -> to Server:
            bit_0: CROSSING - Robot is crossing boundary - 0.5m away from a boundary.
            bit_1: STOP/OBSTACLE - Obstacle detected. 3m away from an obstacle.
            bit_2: RESTART/CLEARED - Obstacle clear          
    */ 
    
    /* Update status */
    for(uint r = 0; r < ROBOT_NUM; ++r) {
        if(_packet_fromS[r].to_uint() & STOP) {
            /* Avoid Collision, Stop robot */
            robotMap[r].STATUS = STOPPED;
            cout << "@: " << sc_time_stamp() << "\n";
            printf("Environment: Robot %d stopped by server\n", r+1);
            printf("Speed: %f\n", RSDS[r].speed);
        } else if(_packet_fromS[r].to_uint() & CONTINUE) {
            /* Next Grid clear, Keep moving */
            robotMap[r].STATUS = MOVING;
            if(RSDS[r].speed < ROBOT_SPEED_MAX) {
                RSDS[r].speed += ROBOT_STEP_SIZE;
            }
            /* Update Next Grid if list is not empty*/
            if(!RSDS[r].NG.empty()) {
                RSDS[r].NG.pop_front();
            }
            /* Update Current Grid if list is not empty*/
            if(!RSDS[r].CG.empty()) {
                RSDS[r].CG.pop_front();
            }
            cout << "@: " << sc_time_stamp() << "\n";
            printf("Environment: Robot %d: Continue moving pass boundary\n", r+1);
            printf("@CG: %d NG: %d\n", RSDS[r].CG.front(), RSDS[r].NG.front());
        } else if(_packet_fromS[r].to_uint() & START) {
            /* Start signal from Server */
            robotMap[r].STATUS = MOVING;
        }
    } 

    for(uint r = 0; r < ROBOT_NUM; ++r) {
        /* If robot has been started */
        if((_packet_fromS[r].to_uint() & START) 
        /* AND if robot has not been stopped */
        && (robotMap[r].STATUS != STOPPED) 
        /* AND if robot not at end of its path */
        && (!RSDS[r].NG.empty())) {
            printf("Speed: %f\n", RSDS[r].speed);
            uint N = map[robotMap[r]._g_x][robotMap[r]._g_y].N;
            uint S = map[robotMap[r]._g_x][robotMap[r]._g_y].S;
            uint W = map[robotMap[r]._g_x][robotMap[r]._g_y].W;
            uint E = map[robotMap[r]._g_x][robotMap[r]._g_y].E;
            cout << "@: " << sc_time_stamp() << "\n";
            printf("Environment: Robot %d, N: %d, S: %d, W: %d, E: %d\n", r+1, N, S, W, E);

            /* Move robot */
            if(N == RSDS[r].NG.front()) {
                /* Move Up */
                robotMap[r]._r_y += RSDS[r].speed;
                cout << "@: " << sc_time_stamp() << "\n";
                printf("Environment: Robot %d moving North to Grid: %d\n", r+1, N);
                printf("Environment: Current grid Coord: gx:%d gy:%d\n", robotMap[r]._g_x, robotMap[r]._g_y);
                printf("Environment: Current Coord: x:%f y:%f\n", robotMap[r]._r_x, robotMap[r]._r_y);
            } else if(S == RSDS[r].NG.front()) {
                /* Move Down */
                robotMap[r]._r_y -= RSDS[r].speed;
                cout << "@: " << sc_time_stamp() << "\n";
                printf("Environment: Robot %d moving South to Grid: %d\n", r+1, S);
                printf("Environment: Current grid Coord: gx:%d gy:%d\n", robotMap[r]._g_x, robotMap[r]._g_y);
                printf("Environment: Current Coord: x:%f y:%f\n", robotMap[r]._r_x, robotMap[r]._r_y);
            } else if(W == RSDS[r].NG.front()) {
                /* Move Left */
                robotMap[r]._r_x -= RSDS[r].speed;
                cout << "@: " << sc_time_stamp() << "\n";
                printf("Environment: Robot %d moving West to Grid: %d\n", r+1, W);
                printf("Environment: Current grid Coord: gx:%d gy:%d\n", robotMap[r]._g_x, robotMap[r]._g_y);
                printf("Environment: Current Coord: x:%f y:%f\n", robotMap[r]._r_x, robotMap[r]._r_y);
            } else if(E == RSDS[r].NG.front()) {
                /* Move Right */
                robotMap[r]._r_x += RSDS[r].speed;
                cout << "@: " << sc_time_stamp() << "\n";
                printf("Environment: Robot %d moving East to Grid: %d\n", r+1, E);
                printf("Environment: Current grid Coord: gx:%d gy:%d\n", robotMap[r]._g_x, robotMap[r]._g_y);
                printf("Environment: Current Coord: x:%f y:%f\n", robotMap[r]._r_x, robotMap[r]._r_y);
            }
        }
    }
}

/*
    Update Obstacle Positions
*/
void environment::update_obstacle_pos() {
    // modulo indexes to reference the obstacle paths
    for(uint o = 0; o < OBSTACLE_NUM; ++o) {
        uint N = map[obstacleMap[o]._g_x][obstacleMap[o]._g_y].N;
        uint S = map[obstacleMap[o]._g_x][obstacleMap[o]._g_y].S;
        uint W = map[obstacleMap[o]._g_x][obstacleMap[o]._g_y].W;
        uint E = map[obstacleMap[o]._g_x][obstacleMap[o]._g_y].E;
        uint size = obstacleMap[o].G.size();

        /* Move Obstacle (Human) */
        if(N == obstacleMap[o].G[obstacleMap[o].n % size]) {
            /* Move Up */
            obstacleMap[o]._o_y += obstacleMap[o].speed;
            cout << "@: " << sc_time_stamp() << "\n";
            printf("Environment: Obstacle %d moving North to Grid: %d\n", o+1, N);
            printf("Environment: Current Coord: x:%f y:%f\n", obstacleMap[o]._o_x, obstacleMap[o]._o_y);
        } else if(S == obstacleMap[o].G[obstacleMap[o].s % size]) {
            /* Move Down */
            obstacleMap[o]._o_y -= obstacleMap[o].speed;
            cout << "@: " << sc_time_stamp() << "\n";
            printf("Environment: Obstacle %d moving South to Grid: %d\n", o+1, S);
            printf("Environment: Current Coord: x:%f y:%f\n", obstacleMap[o]._o_x, obstacleMap[o]._o_y);
        } else if(W == obstacleMap[o].G[obstacleMap[o].w % size]) {
            /* Move Left */
            obstacleMap[o]._o_x -= obstacleMap[o].speed;
            cout << "@: " << sc_time_stamp() << "\n";
            printf("Environment: Obstacle %d moving West to Grid: %d\n", o+1, W);
            printf("Environment: Current Coord: x:%f y:%f\n", obstacleMap[o]._o_x, obstacleMap[o]._o_y);
        } else if(E == obstacleMap[o].G[obstacleMap[o].e % size]) {
            /* Move Right */
            obstacleMap[o]._o_x += obstacleMap[o].speed;
            cout << "@: " << sc_time_stamp() << "\n";
            printf("Environment: Obstacle %d moving East to Grid: %d\n", o+1, E);
            printf("Environment: Current Coord: x:%f y:%f\n", obstacleMap[o]._o_x, obstacleMap[o]._o_y);
        }
    }
}

/*
    Check if any robot is close to the boundary
*/
void environment::robot_boundary_check() {
    for(uint r = 0; r < ROBOT_NUM; ++r) {
        uint N = map[robotMap[r]._g_x][robotMap[r]._g_y].N;
        uint S = map[robotMap[r]._g_x][robotMap[r]._g_y].S;
        uint W = map[robotMap[r]._g_x][robotMap[r]._g_y].W;
        uint E = map[robotMap[r]._g_x][robotMap[r]._g_y].E;

        /* Move robot */
        if(N == RSDS[r].NG.front()) {
            /* Check if .5 meters away from North Boundary */
            if((robotMap[r]._r_y) <= (map[robotMap[r]._g_x - 1][robotMap[r]._g_y].LL.y - ROBOT_STEP_SIZE)) {
                _packet_toS[_e_r_bit_CROSSING] = 1;
                robotMap[r]._g_x -= 1;
            }else {
                _packet_toS[_e_r_bit_CROSSING] = 0;
            }
            /* Stop robot if boundary reached */
            if((robotMap[r]._r_y) == (map[robotMap[r]._g_x - 1][robotMap[r]._g_y].LL.y)) {
                if(!(_packet_fromS[r].to_uint() & CONTINUE)) {
                    robotMap[r].STATUS == STOPPED;
                    cout << "@: " << sc_time_stamp() << "\n";
                    printf("Environment: Robot %d stopped, boundary reached\n", r+1);
                }
            }
        } else if(S == RSDS[r].NG.front()) {
            /* Check if .5 meters away from South Boundary */
            if((robotMap[r]._r_y) <= (map[robotMap[r]._g_x + 1][robotMap[r]._g_y].UR.y + ROBOT_STEP_SIZE)) {
                _packet_toS[_e_r_bit_CROSSING] = 1;
                robotMap[r]._g_x == 1;
            } else {
                _packet_toS[_e_r_bit_CROSSING] = 0;
            }
            /* Stop robot if boundary reached */
            if((robotMap[r]._r_y) == (map[robotMap[r]._g_x + 1][robotMap[r]._g_y].UR.y)) {
                if(!(_packet_fromS[r].to_uint() & CONTINUE)) {
                    robotMap[r].STATUS == STOPPED;
                    cout << "@: " << sc_time_stamp() << "\n";
                    printf("Environment: Robot %d stopped, boundary reached\n", r+1);
                }
            }
        } else if(W == RSDS[r].NG.front()) {
            /* Check if .5 meters away from West Boundary */
            if((robotMap[r]._r_x) <= (map[robotMap[r]._g_x][robotMap[r]._g_y - 1].UR.x + ROBOT_STEP_SIZE)) {
                _packet_toS[_e_r_bit_CROSSING] = 1;
                robotMap[r]._g_y -= 1;
            } else {
                _packet_toS[_e_r_bit_CROSSING] = 0;
            }
            /* Stop robot if boundary reached */
            if((robotMap[r]._r_x) == (map[robotMap[r]._g_x][robotMap[r]._g_y - 1].UR.x)) {
                if(!(_packet_fromS[r].to_uint() & CONTINUE)) {
                    robotMap[r].STATUS == STOPPED;
                    cout << "@: " << sc_time_stamp() << "\n";
                    printf("Environment: Robot %d stopped, boundary reached\n", r+1);
                }
            }
        } else if(E == RSDS[r].NG.front()) {
            /* Check if .5 meters away from East Boundary */
            if((robotMap[r]._r_x) >= (map[robotMap[r]._g_x][robotMap[r]._g_y + 1].LL.x - ROBOT_STEP_SIZE)) {
                _packet_toS[_e_r_bit_CROSSING] = 1;
                robotMap[r]._g_y += 1;
            } else {
                _packet_toS[_e_r_bit_CROSSING] = 0;
            }
            /* Stop robot if boundary reached */
            if((robotMap[r]._r_x) == (map[robotMap[r]._g_x][robotMap[r]._g_y + 1].LL.x)) {
                if(!(_packet_fromS[r].to_uint() & CONTINUE)) {
                    robotMap[r].STATUS == STOPPED;
                    cout << "@: " << sc_time_stamp() << "\n";
                    printf("Environment: Robot %d stopped, boundary reached\n", r+1);
                }
            }
        }
    }
}

/*
    Check if any robot might collide with an obstacle
*/
void environment::robot_collision_check() {
    for(uint r = 0; r < ROBOT_NUM; ++r) {
        uint N = map[robotMap[r]._g_x][robotMap[r]._g_y].N;
        uint S = map[robotMap[r]._g_x][robotMap[r]._g_y].S;
        uint W = map[robotMap[r]._g_x][robotMap[r]._g_y].W;
        uint E = map[robotMap[r]._g_x][robotMap[r]._g_y].E;
        
        if(N == RSDS[r].NG.front()) {
            
        } else if(S == RSDS[r].NG.front()) {

        } else if(W == RSDS[r].NG.front()) {

        } else if(E == RSDS[r].NG.front()) {

        }
    }
}

/*
    Update the robot & obstacle positions.
    Determine if the robot is crossing a boarder,
    about to collide with obstacle, or if it is clear
    of an obstacle.
*/
void environment::environment_update() {
    while(true) {
        wait();
            /* Update Robot Position */
            update_robot_pos();

            /* Update Obstacle Positions */
            // Not working ---> //update_obstacle_pos();

            /* Boundary Check */
            robot_boundary_check();

            /* Robot-Obstacle Distance Check */
            // Not working ---> //robot_collision_check();

            /* Speed results */
            r1_speed.write(RSDS[0].speed);
            r2_speed.write(RSDS[1].speed);
            r3_speed.write(RSDS[2].speed);
            r4_speed.write(RSDS[3].speed);

            /* 
                Finished processing packet from Server. 
                Transmit reply.
            */
            cout << "@: " << sc_time_stamp() << "\n";
            printf("Environment Updated\n");
            _e_tx.notify();   
    }
}

/*
    Transmit the new packet to the Server
*/
void environment::environment_tx() {
    while(true) {
        wait();
        /* Transmit packet to Robot */
        for(int i = 0; i < ROBOT_NUM; ++i) {
             packet_toS[i].write(_packet_toS[i]);
        }
        cout << "@: " << sc_time_stamp() << "\n";
        printf("TX: Environment: to Robot->Server\n");
        for(int i = 0; i < ROBOT_NUM; ++i) {
            cout << "TX: _packet_toS" << i+1 << ":" << _packet_toS[i] << endl;
        }
    }
}
