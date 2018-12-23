//=== COMMUNICATION INTERFACE ===//
//
// File : packet_translator.cpp
//
//===============================//
#include "packet_translator.h"

void packet_translator::process_packet_translator() {
    if(clear || !reset) {
		count = 0;
		error = 0;
        payload = 0;
    } else {
		if(in_data.read().range(11, 8)) {
			payload = in_data.read().range(7, 4);
			count_temp++;
			count = count_temp;
			if(!in_data.read().range(0, 0)) {
				error_temp++;
				error = error_temp;
			}
		}
    }
}
