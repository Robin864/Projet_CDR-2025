#pragma once

#include <vector>
#include "Action.h"

using namespace std;

vector<Action> actions = {
    Action(gotoRelative, 500, 0), // Forward
    Action(gotoRelative, -500, 0), // Backward
    Action(gotoRelative, 0, 500), // Left
    Action(gotoRelative, 0, -500), // Right
    Action(gotoRelative, 500, 500), // Diag 1
    Action(gotoRelative, 500, -500), // Diag 2
    Action(gotoRelative, -500, 500), // Diag 3
    Action(gotoRelative, -500, -500), // Diag 4
    Action(rotateLeft, 90),
    Action(rotateRight, 90),
};