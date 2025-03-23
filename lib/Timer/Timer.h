#pragma once

#include <Arduino.h>
#include "utils.h"

static const int DEFAULT_CLK = 80;
static const int DIVIDER[3] = {
    60 * 1000 * 1000,
    1000 * 1000,
    1000
};
static int instanceNbr = 0; // TODO: identify timer amount on ESP

enum TimeUnit {
    minutes,
    seconds,
    milliseconds
};

class Timer {
private:
    hw_timer_t *timer = NULL;
    int initialDuration;
    TimeUnit initialUnit = seconds;
    bool started = false;
    int getTime(int type, TimeUnit unit = seconds);

public:
    Timer();
    Timer(void (*fn)(void), int callbackAt, TimeUnit unit = seconds, bool loopCallback = true, uint16_t clockDivider = DEFAULT_CLK); // Call function after given time unit
    // TODO: destroyer
    void start();
    void stop();
    void restart();
    void release();
    int getElapsedTime(TimeUnit unit = seconds);
    int getRemainingTime(TimeUnit unit = seconds);
};