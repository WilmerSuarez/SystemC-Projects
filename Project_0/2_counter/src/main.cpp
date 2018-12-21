//====== COUNTER ======//
//
// File : main.cpp
//
//=====================//
#include "counter_1.h"
#include "counter_2.h"
#include "comparator.h"
#include "monitor.h"
#include "driver.h"

int sc_main(int argc, char* argv[]) {
    // ----- CLOCK ----- //
    sc_clock tb_clock ("tb_clock", 1, SC_NS);

    // ----- PORTS ----- //
    sc_signal <bool> tb_load_1, tb_load_2, tb_dec_1, tb_dec_2, tb_overflow_1, tb_overflow_2, tb_ended;
    sc_signal <sc_uint<8> > tb_in_1, tb_in_2, tb_in_3, tb_count_1, tb_count_2;

    // ----- MODULES ----- //
    counter_1 counter1("counter_1");
    counter_2 counter2("counter_2");
    comparator comparator1("comparator_1");
    monitor monitor1("monitor_1");
    driver driver1("driver_1");

    // ----- TRACE FILE ----- //
    sc_trace_file *trace_file = sc_create_vcd_trace_file("counter");

    // ----- SIGNAL ASSOCIATION ----- //
    counter1(tb_in_1, tb_clock, tb_load_1, tb_dec_1, tb_overflow_1, tb_count_1);
    counter2(tb_in_2, tb_in_3, tb_clock, tb_load_2, tb_dec_2, tb_overflow_2, tb_count_2);
    comparator1(tb_count_1, tb_count_2, tb_overflow_1, tb_overflow_2, tb_ended);
    monitor1(tb_in_1, tb_in_2, tb_in_3, tb_count_1, tb_count_2, tb_load_1, tb_load_2, tb_dec_1, tb_dec_2, tb_overflow_1, tb_overflow_2, tb_ended);
    driver1(tb_in_1, tb_in_2, tb_in_3, tb_load_1, tb_load_2, tb_dec_1, tb_dec_2);

    // ----- SIGNAL TRACE ----- //
    sc_trace(trace_file, tb_clock, "tb_clock");
    sc_trace(trace_file, tb_in_1, "tb_in_1");
    sc_trace(trace_file, tb_in_2, "tb_in_2");
    sc_trace(trace_file, tb_in_3, "tb_in_3");
    sc_trace(trace_file, tb_load_1, "tb_load_1");
    sc_trace(trace_file, tb_load_2, "tb_load_2");
    sc_trace(trace_file, tb_dec_1, "tb_dec_1");
    sc_trace(trace_file, tb_dec_2, "tb_dec_2");
    sc_trace(trace_file, tb_overflow_1, "tb_overflow_1");
    sc_trace(trace_file, tb_overflow_2, "tb_overflow_2");
    sc_trace(trace_file, tb_count_1, "tb_count_1");
    sc_trace(trace_file, tb_count_2, "tb_count_2");
    sc_trace(trace_file, tb_ended, "tb_ended");

    // ----- START ----- //
    sc_start(50, SC_NS);
    sc_close_vcd_trace_file(trace_file);
    return 0;
}
