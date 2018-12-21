// ============== ROBOT NAVIGATION ============== //
// 
// File : monitor.cpp
// Navigate Robot.
//
// ============================================== //
//#include "defs.h"
#include "robot.h"
#include "server.h"
#include "environment.h"
#include "monitor.h"

/*  
    Map containing the X & Y coordinates 
    of the Lower Left and Uper Right 
    corners of the Grids
*/
struct gridcoord map[MAX_GRID_INDEX] = { 0 };

/* Contains the status of each robot */
struct RDS RDS[ROBOT_NUM];

int sc_main(int argc, char *argv[]) {
    // ----- CLOCK ----- //
    sc_clock tb_clock ("tb_clock", 1, SC_SEC);

    // ----- ROBOT PATH ----- //
    const std::vector<uint> robotPath = { 
        0, 
        1, 
        2, 
        3, 
        4 
    };

    // ----- PORTS ----- //
    sc_signal<bool> tb_packet_validS, tb_packet_validE;
    sc_signal<sc_bv<3> > tb_packet_fromE, tb_packet_fromS, tb_packet_toE, tb_packet_toS;

    // ----- MODULES ----- //
    robot robot("ROBOT");
    server server("SERVER", robotPath); 
    environment environment("ENVIRONMENT");
    monitor monitor("MONITOR");

    // ----- SIGNAL ASSOCIATION ----- //
    robot(tb_packet_validS, tb_packet_validE, tb_packet_fromE, tb_packet_fromS, tb_packet_toE, tb_packet_toS);
    server(tb_clock, tb_packet_toS, tb_packet_fromS, tb_packet_validS);
    environment(tb_clock, tb_packet_toE, tb_packet_fromE, tb_packet_validE);
    monitor(tb_packet_validS, tb_packet_validE, tb_packet_fromE, tb_packet_fromS, tb_packet_toE, tb_packet_toS);

    // ----- TRACE FILE ----- //
    //sc_trace_file *trace_file = sc_create_vcd_trace_file("ROBOT NAVIGATION");

    /*// ----- SIGNAL TRACE ----- //
    sc_trace(trace_file, tb_clock, "tb_clock");
    sc_trace(trace_file, tb_clear, "tb_clear");
    sc_trace(trace_file, tb_reset, "tb_reset");
    sc_trace(trace_file, sequence_detector_1.first, "seq(0)");
    sc_trace(trace_file, sequence_detector_1.second, "seq(1)");
    sc_trace(trace_file, sequence_detector_1.third, "seq(2)");
    sc_trace(trace_file, sequence_detector_1.fourth, "seq(3)");
    sc_trace(trace_file, tb_input, "tb_input");
    sc_trace(trace_file, tb_output, "tb_output");*/

    // ----- START ----- //
    sc_start(10, SC_SEC);
    //sc_close_vcd_trace_file(trace_file);
    return 0;
}