// ===== GAZE BEHAVIOR MONITORING SYSTEM ===== //
// 
// File : main.cpp
//
// =========================================== //
#include "defs.h"
#include "sensor.h"
#include "mobile.h"
#include "server.h"
#include "timer.h"

/* Max Server to Mobile Packet Count */
//#define MAX_P_COUNT    8192 // 8192 * 1Kbits
#define MAX_P_COUNT    8  // 8 * 1Mbits

/* Server to Mobile Packet Size */
//#define S2M_PACKET_SIZE 1024    // 1Kbits
#define S2M_PACKET_SIZE 1048576 // 1Mbits

/* Bandwidth sizes */
//#define BW             (1024 * 1024)        // 1 Mbps 
//#define BW             (1024 * 1024 * 5)    // 5 Mbps
#define BW             (1024 * 1024 * 10)   // 10 Mbps

const double packet_transmit_time ((PACKET_SIZE * TUPLE_ENTRIES_N * BIT_SIZE) / (double)BW);

/* 
    Calculate the Image transmission start times 
*/
static std::vector<sc_time>
calculate_times(std::vector<sc_time> s_times) {
    std::vector<sc_time> t;
    sc_time temp;
    double ttime = (IMG_SIZE/(double)BW) * MOBILE_NUM;
    double ftime = 0;
    
    /* Initial Transmission Start Times */
    for(uint i = 0; i < IMG_NUM; ++i) {
        ftime = (s_times[i].to_double() / 1000) - ttime;
        temp = sc_time(ftime, SC_SEC);
        t.push_back(temp);
    }

    /* Caclualte Start Time push-back (Update Transmission Start Times) */
    double sub = 0;
    uint j = 0;
    for(int i = (IMG_NUM - 1); i >= 0; --i) {
        if(i) {
            j = i-1;
            if(t[i] < s_times[j]) {
                sub = (s_times[j].to_double() / 1000) - (t[i].to_double() / 1000);
                t[j] = sc_time(((t[j].to_double() / 1000) - sub), SC_SEC);
            }
        }
    }

    return t;
}

int sc_main(int argc, char *argv[]) {
    /* Set Time Resolution */
    sc_set_time_resolution(1, SC_MS);

    /* ----- CLOCK ----- */
    /* 10 ms Sensor Sample Rate (100 HZ) */
    sc_clock tb_sclock ("tb_sclock", 10, SC_MS);    

    /* ----- Images start times ----- */
    /* Case - 1 */
    // sc_time first(200, SC_SEC);
    // sc_time second(220, SC_SEC);
    // sc_time third(225, SC_SEC);
    // sc_time fourth(230, SC_SEC);
    // sc_time fifth(250, SC_SEC);
    /* Case - 2 */
    sc_time first(150, SC_SEC);
    sc_time second(175, SC_SEC);
    sc_time third(200, SC_SEC);
    sc_time fourth(225, SC_SEC);
    sc_time fifth(250, SC_SEC);
    std::vector<sc_time> s_times = {first, second, third, fourth, fifth};
    /* Calcualte Image Transmission start times */
    std::vector<sc_time> t_times = calculate_times(s_times);

    // ----- MODULES ----- //
    mobile mobile_1("MOBILE_1", MAX_P_COUNT, packet_transmit_time);
    mobile mobile_2("MOBILE_2", MAX_P_COUNT, packet_transmit_time);
    mobile mobile_3("MOBILE_3", MAX_P_COUNT, packet_transmit_time);
    mobile mobile_4("MOBILE_4", MAX_P_COUNT, packet_transmit_time);
    server server("SERVER", t_times, packet_transmit_time, MAX_P_COUNT, S2M_PACKET_SIZE, BW);

    // ----- PORTS ----- //
    /* Server Ports */
    sc_signal<bool, SC_MANY_WRITERS> tb_busy;
    sc_signal<bool> tb_m1_request, tb_m2_request, tb_m3_request, tb_m4_request, tb_response_1, tb_response_2, tb_response_3, tb_response_4;
    sc_signal<sc_bv<3> > tb_m1_status, tb_m2_status, tb_m3_status, tb_m4_status;
    sc_signal<bool> tb_img_packet_m1, tb_img_packet_m2, tb_img_packet_m3, tb_img_packet_m4;

    // ----- SIGNAL ASSOCIATION ----- //
    mobile_1(tb_sclock, tb_busy, tb_response_1, tb_img_packet_m1, tb_m1_request, tb_m1_status);
    mobile_2(tb_sclock, tb_busy, tb_response_2, tb_img_packet_m2, tb_m2_request, tb_m2_status);
    mobile_3(tb_sclock, tb_busy, tb_response_3, tb_img_packet_m3, tb_m3_request, tb_m3_status);
    mobile_4(tb_sclock, tb_busy, tb_response_4, tb_img_packet_m4, tb_m4_request, tb_m4_status);
    server(tb_sclock, tb_m1_request, tb_m2_request, tb_m3_request, tb_m4_request, tb_m1_status, tb_m2_status, tb_m3_status, tb_m4_status, tb_response_1, tb_response_2, tb_response_3, tb_response_4, tb_busy, tb_img_packet_m1, tb_img_packet_m2, tb_img_packet_m3, tb_img_packet_m4);

    // ----- START ----- //
    sc_start(250, SC_SEC);
    return 0;
}
