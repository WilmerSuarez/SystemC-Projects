// ===== GAZE BEHAVIOR MONITORING SYSTEM ===== //
// 
// File : main.cpp
//
// =========================================== //
#include "defs.h"
#include "sensor.h"
#include "mobile.h"
#include "server.h"

int sc_main(int argc, char *argv[]) {
    /* ----- CLOCK ----- */
    /* 10 ms Sensor Sample Rate (100 HZ)*/
    sc_clock tb_sclock ("tb_sclock", 10, SC_MS);    
    
    // ----- MODULES ----- //
    sensor sensor_1("SENSOR_1");
    mobile mobile_1("MOBILE_1");
    sensor sensor_2("SENSOR_2");
    mobile mobile_2("MOBILE_2");
    server server("SERVER");

    // ----- PORTS ----- //
    /* Sensor Ports */
    sc_signal<sc_uint<10> > tb_gp_x_1, tb_gp_y_1, tb_gp_x_2, tb_gp_y_2;
    /* Server Ports */
    sc_signal<bool> tb_m1_request, tb_m2_request, tb_busy, tb_response_1, tb_response_2;
    sc_signal<sc_bv<3> > tb_m1_status, tb_m2_status;

    // ----- SIGNAL ASSOCIATION ----- //
    sensor_1(tb_sclock, tb_gp_x_1, tb_gp_y_1);
    mobile_1(tb_gp_x_1, tb_gp_y_1, tb_busy, tb_response_1, tb_m1_request, tb_m1_status);
    sensor_2(tb_sclock, tb_gp_x_2, tb_gp_y_2);
    mobile_2(tb_gp_x_2, tb_gp_y_2, tb_busy, tb_response_2, tb_m2_request, tb_m2_status);
    server(tb_m1_request, tb_m2_request, tb_m1_status, tb_m2_status, tb_busy, tb_response_1, tb_response_2);

    // ----- START ----- //
    sc_start(750, SC_MS);
    //sc_start(10, SC_SEC);
    return 0;
}
