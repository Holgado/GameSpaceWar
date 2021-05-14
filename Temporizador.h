//
//  ControlaTempo.hpp
//  Imagens
//
//  Created by Márcio Sarroglia Pinho on 23/03/20.
//  Copyright © 2020 rmd. All rights reserved.
//

#ifndef ControlaTempo_hpp
#define ControlaTempo_hpp

#include <iostream>
using namespace std;

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


class Temporizador
{
#ifdef WIN32
    DWORD start_time;
#else
    struct timeval start_time;
#endif
public:
    Temporizador() { // Inicializa o temporizador
        #ifdef _WIN32
            start_time = GetTickCount();
        #else
            gettimeofday(&start_time, NULL);
        #endif
    }
    double getDeltaT() {
        double dt;

        #ifdef _WIN32
            DWORD end_time;
            end_time = GetTickCount();
            dt = (float) (end_time - start_time) / 1000.0;
        #else
            // Figure out time elapsed since last call to idle function
            struct timeval end_time;
            gettimeofday(&end_time, NULL);
            dt = (float)(end_time.tv_sec  - start_time.tv_sec) + 1.0e-6*(end_time.tv_usec - start_time.tv_usec);
        #endif
        start_time = end_time;
        return dt;
    }
};

#endif /* ControlaTempo_hpp */
