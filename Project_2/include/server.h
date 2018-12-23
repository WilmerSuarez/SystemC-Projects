// ============== GAZE BEHAVIOR MONITORING SYSTEM ============== //
// 
// File : server.h
// This module 
//
// ============================================================= //
#ifndef __SERVER_H__
#define __SERVER_H__
#include "defs.h"

class server : public sc_module {
    public:
        // ----- PORTS ----- //

        // ----- CONSTRUCTOR ----- //
        SC_HAS_PROCESS(server);
        server(sc_module_name name) : 
        sc_module(name) {

            /* Output Ports Initialization */
            
        }
    private:
        // ----- METHODS ----- //

        // ----- INTERNAL VARIABLES ----- //
};

#endif // __SERVER_H__
