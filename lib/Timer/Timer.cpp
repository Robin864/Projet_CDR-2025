#include "Timer.h"

Timer::Timer() {}

Timer::Timer(void (*function)(void), int duration, TimeUnit unit, bool loopCallback, uint16_t clockDivider)
{
    if (duration >= 1)
    {
        timer = timerBegin(instanceNbr, clockDivider, true);
        timerAttachInterrupt(timer, function, false);
        timerAlarmWrite(timer, duration*DIVIDER[unit], loopCallback);
        initialDuration = duration*DIVIDER[unit];
        initialUnit = unit;
        instanceNbr++;
    }
    else
    {
        ERROR("timer failed to init due to non-int given duration");
        // TODO: destroyer
    }
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

int Timer::getTime(int type, TimeUnit unit) // True is elapsed, false remaining
{
    int elapsedTime = timerRead(timer) / DIVIDER[unit];

    if (elapsedTime > initialDuration / DIVIDER[unit] || elapsedTime < 0 || !started)
        return -1;
    else
        return (int) (type ? elapsedTime : initialDuration - elapsedTime);
}

int Timer::getElapsedTime(TimeUnit unit)
{
    return getTime(1, unit);
}

int Timer::getRemainingTime(TimeUnit unit)
{
   return getTime(0, unit);
}