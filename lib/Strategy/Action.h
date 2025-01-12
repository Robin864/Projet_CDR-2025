#pragma once

enum ActionType
{
    gotoAbsolute, // 0
    gotoRelative,
    rotateAbsolute,
    rotateRelative,
    grabPlank,
    ungrabPlank,
    grabPot,
    ungrabPot
};

class Action
{
public:
    ActionType type;
    float param1; 
    float param2;
    
    Action(ActionType _type, float _param1 = 0, float _param2 = 0)
    {
        type = _type;
        param1 = _param1;
        param2 = _param2;
    }
};