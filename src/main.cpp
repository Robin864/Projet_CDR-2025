#include <Arduino.h>

#include "UniBoardV4Def.h"

#include "Strategy.h"

Strategy strategy;

void setPinsStates()
{
    pinMode(TEAM_PIN, INPUT_PULLUP);
    pinMode(INIT_PIN, INPUT_PULLUP);
    pinMode(TIR_PIN, INPUT_PULLUP);

    pinMode(PIN::Steppers::EN, OUTPUT);
    digitalWrite(PIN::Steppers::EN, LOW);
}

void setup()
{
    Serial.begin(115200);

    setPinsStates();

    strategy.setup();
}

void loop()
{

}