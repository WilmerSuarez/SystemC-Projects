// ===== GAZE BEHAVIOR MONITORING SYSTEM ===== //
// 
// File : sensor.cpp
// This module is used to generate the 
// gazepoints for the mobiles
//
// =========================================== //
#include <random>
#include <chrono>
#include "sensor.h"

/*
    Generates Gazepoint coordinates (x & y)
    every 10 ms (100 samples/sec)
*/
void sensor::sensor_proc() {
    while(true) {
        wait();
        /* Generate unique seed */
        uint seed = std::chrono::steady_clock::now().time_since_epoch().count();
        /* Create default random engine using the seed */
        std::default_random_engine r(seed);
        /* Distribute the random number. Range: [0, 1023] */
        std::uniform_int_distribution<uint> d(0, 1023);

        /* Generate Gazepoint */
        gp_x.write(d(r));
        gp_y.write(d(r));
    }
}
