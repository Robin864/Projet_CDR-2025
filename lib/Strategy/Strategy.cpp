#include "Strategy.h"

#include "strat-0.h"

Strategy::Strategy() {}

String Strategy::teamCoord(int _x, int _y)
{
    int teamFactor = (team == 'y' ? 0 : 1), boardWidth = 2000;
    
    int newY = abs((boardWidth * teamFactor) - _y);
    return (String) "(" + _x + "," + newY + ")";
}

void Strategy::setup()
{
    movement.setup();
}

void Strategy::selectTeam()
{
    if (digitalRead(TEAM_PIN) == LOW)
        team = 'b';
    else if (digitalRead(TEAM_PIN) == HIGH)
        team = 'y';
    else
        ERROR("unable to select team");
}

void Strategy::init()
{}

void Strategy::execAction(Action action)
{
    switch (action.type)
    {
        case gotoAbsolute:
            movement.moveTo(Point2D(action.param1, action.param2));
            break;
        case gotoRelative:
            movement.moveBy(Point2D(action.param1, action.param2));
            break;
        case rotateAbsolute:
            movement.rotateTo(action.param1);
            break;
        case rotateLeft:
            movement.rotateLeftBy(action.param1);
        case rotateRight:
            movement.rotateRightBy(action.param1);
            break;
        case grabPlank:
            Serial.println("Grabing plank...");
            break;
        case ungrabPlank:
            Serial.println("Ungrabing plank...");
            break;
        case grabPot:
            Serial.println("Grabing pot...");
            break;
        case ungrabPot:
            Serial.println("Ungrabing pot...");
            break;
        default:
            ERROR("wrong action type");
            break;
    }
}

void Strategy::game()
{
    for (const auto& action : actions)
    {
        execAction(action);
    }

    fullstop();
}

void Strategy::fullstop()
{
    movement.fullstop();
}