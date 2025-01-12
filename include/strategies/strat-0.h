#pragma once

#include <vector>
#include "Action.h"

using namespace std;

vector<Action> actions = {
    Action(gotoRelative, 150, 200),
    Action(gotoAbsolute, 400, 500),
    Action(rotateRelative, 23),
    Action(rotateAbsolute, 150),
    Action(grabPlank),
    Action(ungrabPlank),
    Action(grabPot),
    Action(ungrabPot)
};