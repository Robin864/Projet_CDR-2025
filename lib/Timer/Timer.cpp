#include "Timer.h"

Timer::Timer() {}

/**
 * @brief Constructor for the Timer class.
 *
 * Initializes a timer with a callback function, duration, time unit,
 * loop flag, and clock divider.
 *
 * @param function      Pointer to the callback function to execute when the timer expires.
 * @param duration      Duration of the timer. Must be greater than or equal to 1.
 * @param unit          Time unit of the duration (e.g., seconds, milliseconds).
 * @param loopCallback  Indicates whether the callback function should loop.
 * @param clockDivider  Clock divider for the timer.
 *
 * @note If the duration is less than 1, the timer will not be initialized and an error will be reported.
 * @todo Implement a destructor to clean up resources in case of initialization failure.
 */
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

/**
 * @brief Starts the timer.
 *
 * Enables the timer alarm, allowing the timer to begin counting down.
 * Sets the internal `started` flag to true to indicate that the timer is active.
 */
void Timer::start()
{
    timerAlarmEnable(timer);
    started = true;
}

/**
 * @brief Stops the timer.
 *
 * Disables the timer alarm, stopping the timer from counting down.
 * Sets the internal `started` flag to false to indicate that the timer is inactive.
 */
void Timer::stop()
{
    timerStop(timer);
    started = false;
}

/**
 * @brief Restarts the timer.
 *
 * Checks if the timer is configured to auto-reload. If so, restarts the timer.
 * If auto-reload is not configured, logs an error message indicating that no reload is configured.
 *
 * @note The timer must have auto-reload enabled for this method to restart it successfully.
 */
void Timer::restart()
{
    if (timerGetAutoReload(timer))
        timerRestart(timer);
    else
        ERROR("No reload configured for timer " + instanceNbr);
}

/**
 * @brief Releases the timer resources.
 *
 * Ends the timer, freeing up any associated resources.
 *
 * @todo Implement a destructor to properly clean up resources.
 */
void Timer::release()
{
    timerEnd(timer);
    // TODO: destroyer
}

/**
 * @brief Gets the timer's time based on the specified type and unit.
 *
 * Calculates and returns the elapsed time or remaining time of the timer,
 * depending on the value of the `type` parameter.
 *
 * @param type Determines whether to return elapsed time (true) or remaining time (false).
 * @param unit The time unit for the returned value (e.g., seconds, milliseconds).
 *
 * @return The elapsed or remaining time in the specified unit. Returns -1 if the timer is not started
 *         or if the elapsed time is invalid.
 *
 * @note The method returns -1 if the timer has not been started or if the elapsed time is greater
 *       than the initial duration or is negative.
 */
int Timer::getTime(int type, TimeUnit unit) // True is elapsed, false remaining
{
    int elapsedTime = timerRead(timer) / DIVIDER[unit];

    if (elapsedTime > initialDuration / DIVIDER[unit] || elapsedTime < 0 || !started)
        return -1;
    else
        return (int) (type ? elapsedTime : initialDuration - elapsedTime);
}

/**
 * @brief Gets the elapsed time of the timer.
 *
 * Returns the amount of time that has elapsed since the timer started,
 * in the specified time unit.
 *
 * @param unit The time unit for the returned value (e.g., seconds, milliseconds).
 *
 * @return The elapsed time in the specified unit. Returns -1 if the timer is not started
 *         or if the elapsed time is invalid.
 *
 * @note This method calls `getTime` with the type parameter set to 1 to indicate elapsed time.
 */
int Timer::getElapsedTime(TimeUnit unit)
{
    return getTime(1, unit);
}

/**
 * @brief Gets the remaining time of the timer.
 *
 * Returns the amount of time remaining until the timer expires,
 * in the specified time unit.
 *
 * @param unit The time unit for the returned value (e.g., seconds, milliseconds).
 *
 * @return The remaining time in the specified unit. Returns -1 if the timer is not started
 *         or if the remaining time is invalid.
 *
 * @note This method calls `getTime` with the type parameter set to 0 to indicate remaining time.
 */
int Timer::getRemainingTime(TimeUnit unit)
{
   return getTime(0, unit);
}