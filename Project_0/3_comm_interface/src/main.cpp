//=== COMMUNICATION INTERFACE ===//
//
// File : main.cpp
//
//===============================//
#include "packet_translator.h"
#include "monitor.h"
#include "driver.h"

int sc_main(int argc, char* argv[]) {
    // ===== CLOCK ===== //
    sc_clock tb_clock("tb_clock", 1, SC_NS);

    // ----- PORTS ----- //
    sc_signal <bool> tb_reset, tb_clear;
    sc_signal <sc_uint<12> > tb_in_data; 
    sc_signal <sc_uint<8> > tb_count, tb_error;
    sc_signal <sc_uint<4> > tb_payload;

    // ----- MODULES ----- //
    packet_translator packet_translator_1("packet_translator_1");
    driver driver_1("driver_1");
    monitor monitor_1("monitor_1");

    // ----- TRACE FILE ----- //
    sc_trace_file *trace_file = sc_create_vcd_trace_file("packet_translator");

    // ----- SIGNAL ASSOCIATION ----- //
    packet_translator_1(tb_clock, tb_reset, tb_clear, tb_in_data, tb_count, tb_error, tb_payload);
    driver_1(tb_reset, tb_clear, tb_in_data);
    monitor_1(tb_reset, tb_clear, tb_in_data, tb_count, tb_error, tb_payload);

    // ----- SIGNAL TRACE ----- //
    sc_trace(trace_file, tb_clock, "tb_clock");
    sc_trace(trace_file, tb_clear, "tb_clear");
    sc_trace(trace_file, tb_reset, "tb_reset");
    sc_trace(trace_file, tb_in_data, "tb_in_data");
    sc_trace(trace_file, tb_count, "tb_count");
    sc_trace(trace_file, tb_error, "tb_error");
    sc_trace(trace_file, tb_payload, "tb_payload");

    // ----- START ----- //
    sc_start(5, SC_NS);
    sc_close_vcd_trace_file(trace_file);
    return 0;
}
