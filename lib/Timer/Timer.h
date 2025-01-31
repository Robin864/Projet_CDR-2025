#pragma once

#include <Arduino.h>

#include "utils.h"

static const int DEFAULT_CLK = 80;
static const int SECONDS_DIVIDER = 1000000;
static int instanceNbr = 0;

class Timer {
private:
    hw_timer_t *timer = NULL;
    int initialDuration;
    bool started = false;
    int getTime(int type);

public:
    Timer();
    Timer(int callbackAt, void (*fn)(void), bool loop = true, uint16_t clockDivider = DEFAULT_CLK); // Call function after given seconds
    // TODO: destroyer
    void start();
    void stop();
    void restart();
    void release();
    int getElapsedTime();
    int getRemainingTime();
};