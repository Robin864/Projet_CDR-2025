#pragma once

#include <vector>
#include "Action.h"

using namespace std;

vector<Action> actions = {
    Action(gotoAbsolute, 400, 500),
    Action(gotoRelative, 150, 200),
    Action(rotateAbsolute, 150),
    Action(rotateLeft, 150),
    Action(rotateRight, 12),
    Action(grabPlank),
    Action(ungrabPlank),
    Action(grabPot),
    Action(ungrabPot)
};