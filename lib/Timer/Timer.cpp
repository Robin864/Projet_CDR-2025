#include "Timer.h"

Timer::Timer() {}

Timer::Timer(int duration, void (*function)(void), bool loop, uint16_t clockDivider)
{
    timer = timerBegin(instanceNbr, clockDivider, true);
    timerAttachInterrupt(timer, function, false);
    timerAlarmWrite(timer, duration*SECONDS_DIVIDER, loop);
    initialDuration = duration;
    instanceNbr++;
}

void Timer::start()
{
    timerAlarmEnable(timer);
    started = true;
}

void Timer::stop()
{
    timerStop(timer);
}

void Timer::restart()
{
    if (timerGetAutoReload(timer))
        timerRestart(timer);
    else
        ERROR("No reload configured for timer " + instanceNbr);
}

void Timer::release()
{
    timerEnd(timer);
}

int Timer::getTime(int type) // True is elapsed, false remaining
{
    int elapsedTime = timerRead(timer) / SECONDS_DIVIDER;

    if (elapsedTime > initialDuration || elapsedTime < 0 || !started)
        return -1;
    else
        return (int) (type ? elapsedTime : initialDuration - elapsedTime);
}

int Timer::getElapsedTime()
{
    return getTime(1);
}

int Timer::getRemainingTime()
{
   return getTime(0);
}