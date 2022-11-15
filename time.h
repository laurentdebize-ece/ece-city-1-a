//
// Created by Erwan Pillard on 12/11/2022.
//

#ifndef ECE_CITY_1_A_TIME_H
#define ECE_CITY_1_A_TIME_H

#include "stdio.h"
#include "raylib.h"

typedef struct Timer {
    double startTime;   // Start time (seconds)
    double lifeTime;    // Lifetime (seconds)
} Timer;

void StartTimer(Timer *timer, double lifetime);
bool TimerDone(Timer timer);
double GetElapsed(Timer timer);

#endif //ECE_CITY_1_A_TIME_H
