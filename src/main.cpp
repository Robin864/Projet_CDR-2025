#include <Arduino.h>

#include "UniBoardV4Def.h"

#include "Strategy.h"

void fullstop();

Timer timer(&fullstop, DEFAULT_GAME_DURATION, seconds, false);
Strategy strategy;

void setPinsStates()
{
    pinMode(TEAM_PIN, INPUT_PULLUP);
    pinMode(INIT_PIN, INPUT_PULLUP);
    pinMode(TIR_PIN, INPUT_PULLUP);

    pinMode(PIN::Steppers::EN, OUTPUT);
    digitalWrite(PIN::Steppers::EN, LOW);
}

void waitStart()
{
    while(digitalRead(TIR_PIN))
        delay(1);

    while(!digitalRead(TIR_PIN))
        delay(1);
}

void setup()
{
    Serial.begin(115200);

    setPinsStates();

    strategy.setup();
}

void loop()
{
    // strategy.init();
    waitStart();
    timer.start();
    strategy.game();
}

void fullstop()
{
    strategy.fullstop();
}