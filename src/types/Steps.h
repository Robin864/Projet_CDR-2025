#pragma once

#include <Arduino.h>

#include "Point2D.h"
#include "PolarVect.h"

#include "config.h"
using namespace config::Movement;

class Point2D;
class PolarVect;

class Steps
{
private:

public:
    float steps[stepperNb];
    Steps();
    
    Point2D to2D();
    PolarVect toPolar();
};