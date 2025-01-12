#pragma once

#include <Arduino.h>

#include "UniBoardV4Def.h"
#include "utils.h"

#include "Action.h"

#include "Movement.h"

class Strategy
{
private:
    char team;
    Movement movement;
    // Pot pot1
    // Pot pot2
    // Plank plank1
    // Plank plank2
    String teamCoord(int _x, int _y);
    void execAction(Action action);

public:
    void selectTeam();
    void setup();
    void init();
    void game();
};