// ============== ROBOT NAVIGATION ============== //
// 
// File : monitor.cpp
// Navigate Robot.
//
// ============================================== //
#include "defs.h"
#include "robot.h"
#include "server.h"
#include "environment.h"

/*  
    Map containing the X & Y coordinates 
    of the Lower Left and Uper Right 
    corners of the Grids
*/
struct gridcoord map[MAX_GRID_NUM_X][MAX_GRID_NUM_Y] = {
    {{{0, 16}, {2, 18}, 1, 0, 11, 0, 2},     {{2, 16}, {4, 18}, 2, 0, 0, 1, 3},     {{4, 16}, {6, 18}, 3, 0, 0, 2, 4},     {{6, 16}, {8, 18}, 4, 0, 0, 3, 5},     {{8, 16}, {10, 18}, 5, 0, 0, 4, 6},     {{10, 16}, {12, 18}, 6, 0, 0, 5, 7},      {{12, 16}, {14, 18}, 7, 0, 0, 6, 8},      {{14, 16}, {16, 18}, 8, 0, 0, 7, 9},     {{16, 16}, {18, 18}, 9, 0, 0, 8, 10},    {{18, 16}, {20, 18}, 10, 0, 12, 9, 0} }, 
    {{{0, 14}, {2, 16}, 11, 1, 13, 0, 0},    {{2, 14}, {4, 16}, 0, 0, 0, 0, 0},     {{4, 14}, {6, 16}, 0, 0, 0, 0, 0},     {{6, 14}, {8, 16}, 0, 0, 0, 0, 0},     {{8, 14}, {10, 16}, 0, 0, 0, 0, 0},     {{10, 14}, {12, 16}, 0, 0, 0, 0, 0},      {{12, 14}, {14, 16}, 0, 0, 0, 0, 0},      {{14, 14}, {16, 16}, 0, 0, 0, 0, 0},     {{16, 14}, {18, 16}, 0, 0, 0, 0, 0},     {{18, 14}, {20, 16}, 12, 10, 22, 0, 0} }, 
    {{{0, 12}, {2, 14}, 13, 11, 23, 0, 14},  {{2, 12}, {4, 14}, 14, 0, 0, 13, 15},  {{4, 12}, {6, 14}, 15, 0, 0, 14, 16},  {{6, 12}, {8, 14}, 16, 0, 0, 15, 17},  {{8, 12}, {10, 14}, 17, 0, 0, 16, 18},  {{10, 12}, {12, 14}, 18, 0, 24, 17, 19},  {{12, 12}, {14, 14}, 19, 0, 0, 18, 20},   {{14, 12}, {16, 14}, 20, 0, 0, 19, 21},  {{16, 12}, {18, 14}, 21, 0, 0, 20, 22},  {{18, 12}, {20, 14}, 22, 12, 25, 21, 0} }, 
    {{{0, 10}, {2, 12}, 23, 13, 26, 0, 0},   {{2, 10}, {4, 12}, 0, 0, 0, 0, 0},     {{4, 10}, {6, 12}, 0, 0, 0, 0, 0},     {{6, 10}, {8, 12}, 0, 0, 0, 0, 0},     {{8, 10}, {10, 12}, 0, 0, 0, 0, 0},     {{10, 10}, {12, 12}, 24, 18, 31, 0, 0},   {{12, 10}, {14, 12}, 0, 0, 0, 0, 0},      {{14, 10}, {16, 12}, 0, 0, 0, 0, 0},     {{16, 10}, {18, 12}, 0, 0, 0, 0, 0},     {{18, 10}, {20, 12}, 25, 22, 35, 0, 0} }, 
    {{{0, 8}, {2, 10}, 26, 23, 36, 0, 27},   {{2, 8}, {4, 10}, 27, 0, 0, 26, 28},   {{4, 8}, {6, 10}, 28, 0, 0, 27, 29},   {{6, 8}, {8, 10}, 29, 0, 0, 28, 30},   {{8, 8}, {10, 10}, 30, 0, 0, 29, 31},   {{10, 8}, {12, 10}, 31, 24, 0, 30, 32},   {{12, 8}, {14, 10}, 32, 0, 37, 31, 33},   {{14, 8}, {16, 10}, 33, 0, 0, 32, 34},   {{16, 8}, {18, 10}, 34, 0, 0, 33, 35},   {{18, 8}, {20, 10}, 35, 25, 38, 34, 0} }, 
    {{{0, 6}, {2, 8}, 36, 26, 39, 0, 0},     {{2, 6}, {4, 8}, 0, 0, 0, 0, 0},       {{4, 6}, {6, 8}, 0, 0, 0, 0, 0},       {{6, 6}, {8, 8}, 0, 0, 0, 0, 0},       {{8, 6}, {10, 8}, 0, 0, 0, 0, 0},       {{10, 6}, {12, 8}, 0, 0, 0, 0, 0},        {{12, 6}, {14, 8}, 37, 32, 45, 0, 0},     {{14, 6}, {16, 8}, 0, 0, 0, 0, 0},       {{16, 6}, {18, 8}, 0, 0, 0, 0, 0},       {{18, 6}, {20, 8}, 38, 35, 48, 0, 0} }, 
    {{{0, 4}, {2, 6}, 39, 36, 49, 0, 40},    {{2, 4}, {4, 6}, 40, 0, 0, 39, 41},    {{4, 4}, {6, 6}, 41, 0, 0, 40, 42},    {{6, 4}, {8, 6}, 42, 0, 0, 41, 43},    {{8, 4}, {10, 6}, 43, 0, 0, 42, 44},    {{10, 4}, {12, 6}, 44, 0, 0, 43, 45},     {{12, 4}, {14, 6}, 45, 37, 0, 44, 46},    {{14, 4}, {16, 6}, 46, 0, 0, 45, 47},    {{16, 4}, {18, 6}, 47, 0, 0, 46, 48},    {{18, 4}, {20, 6}, 48, 38, 50, 47, 0} }, 
    {{{0, 2}, {2, 4}, 49, 39, 51, 0, 0},     {{2, 2}, {4, 4}, 0, 0, 0, 0, 0},       {{4, 2}, {6, 4}, 0, 0, 0, 0, 0},       {{6, 2}, {8, 4}, 0, 0, 0, 0, 0},       {{8, 2}, {10, 4}, 0, 0, 0, 0, 0},       {{10, 2}, {12, 4}, 0, 0, 0, 0, 0},        {{12, 2}, {14, 4}, 0, 0, 0, 0, 0},        {{14, 2}, {16, 4}, 0, 0, 0, 0, 0},       {{16, 2}, {18, 4}, 0, 0, 0, 0, 0},       {{18, 2}, {20, 4}, 50, 48, 60, 0, 0} }, 
    {{{0, 0}, {2, 2}, 51, 49, 0, 0, 52},     {{2, 0}, {4, 2}, 52, 0, 0, 51, 53},    {{4, 0}, {6, 2}, 53, 0, 0, 52, 54},    {{6, 0}, {8, 2}, 54, 0, 0, 53, 55},    {{8, 0}, {10, 2}, 55, 0, 0, 54, 56},    {{10, 0}, {12, 2}, 56, 0, 0, 55, 57},     {{12, 0}, {14, 2}, 57, 0, 0, 56, 58},     {{14, 0}, {16, 2}, 58, 0, 0, 57, 59},    {{16, 0}, {18, 2}, 59, 0, 0, 58, 60},    {{18, 0}, {20, 2}, 60, 50, 0, 59, 0} }
};

/* Contains all robot status information */
struct RSDS RSDS[ROBOT_NUM] = { 0 };

int sc_main(int argc, char *argv[]) {
    /* ----- CLOCK ----- */
    sc_clock tb_clock ("tb_clock", 1, SC_SEC);

    /* ----- OBSTACLE PATH ----- */
    const std::vector<std::vector<uint> > obstaclePath = { 
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 11}, 
        {13, 14, 15, 16, 17, 18, 24, 31, 30, 29, 28, 27, 26, 23},
        {18, 19, 20, 21, 22, 25, 35, 34, 33, 32, 31, 24},
        {26, 27, 28, 29, 30, 31, 32, 37, 45, 44, 43, 42, 41, 40, 39, 36},
        {32, 33, 34, 35, 38, 48, 47, 46, 45, 37},
        {39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 50, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 49}
    };

    /* ----- ROBOT PATH ----- */
    std::vector<std::list<uint> > robotPath = { 
        {1, 11, 13, 14, 15, 16, 17, 18, 24, 31, 30, 29, 28, 27, 26, 36, 39, 0}, 
        {10, 12, 22, 21, 20, 19, 18, 24, 31, 32, 33, 34, 35, 25, 0},
        {49, 39, 36, 26, 27, 28, 29, 30, 31, 32, 37, 45, 46, 47, 48, 38, 0},
        {60, 50, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 49, 51, 52, 53, 54, 55, 0}
    };

    /* ----- ROBOT START TIMES ----- */
    /* 
        Robot 1: 1 seconds
        Robot 2: 5 seconds
        Robot 3: 7 seconds
        Robot 4: 2 seconds
    */
    sc_time first(1, SC_SEC);
    sc_time second(5, SC_SEC);
    sc_time third(7, SC_SEC);
    sc_time fourth(2, SC_SEC);
    const std::vector<sc_time> robot_S_T = {first, second, third, fourth};

    // ----- PORTS ----- //
    sc_signal<sc_bv<3> > packet_fromER1, packet_fromER2, packet_fromER3, packet_fromER4;
    sc_signal<sc_bv<3> > packet_fromSR1, packet_fromSR2, packet_fromSR3, packet_fromSR4;
    sc_signal<sc_bv<3> > packet_toER1, packet_toER2, packet_toER3, packet_toER4;
    sc_signal<sc_bv<3> > packet_toSR1, packet_toSR2, packet_toSR3, packet_toSR4;
    
    // ----- MODULES ----- //
    robot robot1("ROBOT1");
    robot robot2("ROBOT2");
    robot robot3("ROBOT3");
    robot robot4("ROBOT4");
    server server("SERVER", robotPath, robot_S_T); 
    environment environment("ENVIRONMENT", obstaclePath);
    
    // ----- SIGNAL ASSOCIATION ----- //
    robot1(packet_fromER1, packet_fromSR1, packet_toER1, packet_toSR1);
    robot2(packet_fromER2, packet_fromSR2, packet_toER2, packet_toSR2);
    robot3(packet_fromER3, packet_fromSR3, packet_toER3, packet_toSR3);
    robot4(packet_fromER4, packet_fromSR4, packet_toER4, packet_toSR4);
    server(tb_clock, packet_toSR1, packet_toSR2, packet_toSR3, packet_toSR4, packet_fromSR1, packet_fromSR2, packet_fromSR3, packet_fromSR4);
    environment(tb_clock, packet_toER1, packet_toER2, packet_toER3, packet_toER4, packet_fromER1, packet_fromER2, packet_fromER3, packet_fromER4);
    
    // ----- TRACE FILE ----- //
    sc_trace_file *trace_file = sc_create_vcd_trace_file("robot_navigation");

    // ----- SIGNAL TRACE ----- //
    /* Speed results for each robot */
    sc_trace(trace_file, tb_clock, "tb_clock");
    sc_trace(trace_file, environment.r1_speed, "R1_SPEED");
    sc_trace(trace_file, environment.r2_speed, "R2_SPEED");
    sc_trace(trace_file, environment.r3_speed, "R3_SPEED");
    sc_trace(trace_file, environment.r4_speed, "R4_SPEED");

    // ----- START ----- //
    sc_start(18, SC_SEC);
    sc_close_vcd_trace_file(trace_file);
    return 0;
}
