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
    float angle, distance;
    PolarVect();
    PolarVect(float _angle, float _distance);
    Point2D to2D();
    Steps toSteps();
};