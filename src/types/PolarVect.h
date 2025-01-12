#pragma once

#include <math.h>

#include "Point2D.h"
#include "Steps.h"

class Point2D;
class Steps;

class PolarVect
{
private:

public:
    int angle, distance;
    PolarVect();
    PolarVect(int _angle, int _distance);
    Point2D to2D();
    Steps toSteps();
};