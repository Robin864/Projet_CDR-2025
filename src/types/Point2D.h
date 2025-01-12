#pragma once

#include <math.h>

#include "PolarVect.h"
#include "Steps.h"

class PolarVect;
class Steps;

class Point2D
{
private:

public:
    int x, y;
    Point2D();
    Point2D(int _x, int _y);
    Point2D operator-(const Point2D& other);
    Point2D operator+(const Point2D& other);
    Point2D operator+=(const Point2D& other);

    PolarVect toPolar();
    Steps toSteps(float currentAngle = 0);
};