//============== SEQUENCE DETECTOR ==============
//
// File : main.cpp
// Output 'HIGH' if sequence "1011" is detected.
//
//===============================================
#include "driver.h"
#include "monitor.h"
#include "sequence_detector.cpp"

int sc_main(int argc, char* argv[]) {
    // ----- CLOCK ----- //
    sc_clock tb_clock ("tb_clock", 1, SC_NS);

    // ----- PORTS ----- //
    sc_signal <bool> tb_reset, tb_clear, tb_input, tb_output;

    // ----- MODULES ----- //
    sequence_detector<bool> sequence_detector_1("sequence_detector_1");
    driver driver_1("driver_1");
    monitor monitor_1("monitor_1");

    // ----- TRACE FILE ----- //
    sc_trace_file *trace_file = sc_create_vcd_trace_file("sequence_detector");

    // ----- SIGNAL ASSOCIATION ----- //
    sequence_detector_1(tb_clock, tb_reset, tb_clear, tb_input, tb_output);
    driver_1(tb_reset, tb_clear, tb_input);
    monitor_1(tb_reset, tb_clear, tb_input, tb_output);

    // ----- SIGNAL TRACE ----- //
    sc_trace(trace_file, tb_clock, "tb_clock");
    sc_trace(trace_file, tb_clear, "tb_clear");
    sc_trace(trace_file, tb_reset, "tb_reset");
    sc_trace(trace_file, sequence_detector_1.first, "seq(0)");
    sc_trace(trace_file, sequence_detector_1.second, "seq(1)");
    sc_trace(trace_file, sequence_detector_1.third, "seq(2)");
    sc_trace(trace_file, sequence_detector_1.fourth, "seq(3)");
    sc_trace(trace_file, tb_input, "tb_input");
    sc_trace(trace_file, tb_output, "tb_output");

    // ----- START ----- //
    sc_start(10, SC_NS);
    sc_close_vcd_trace_file(trace_file);
    return 0;
}
