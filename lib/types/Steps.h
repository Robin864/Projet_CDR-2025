#pragma once

#include <Arduino.h>

#include "Point2D.h"
#include "PolarVect.h"
#include "DoubleMap.h"

const byte stepperNb = 4;

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