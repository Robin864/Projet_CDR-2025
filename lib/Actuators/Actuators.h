#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "UniBoardV4Def.h"
#include "utils.h"

#include "config.h"
using namespace config::Actuators;

/*
    ### Tin cans ###
    - Lifter *2
    - Orienter *2
    - Graber *2

    ### Plank ###
    - Lifter *1
    - Orienter *1
    - Graber *1 (Pump)

    ### Banner ###
    - Lifter *1
*/

class Actuators
{
private:
    Adafruit_PWMServoDriver pwm;
    bool cans[2] = {false, false}, planks = false, banner = true;

public:
    Actuators();
    void setup();

    void grabCan(int side);
    void ungrabCan(int side);

    void grabPlank();
    void ungrabPlank();

    void dropBanner();
};