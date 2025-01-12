#include "PolarVect.h"

PolarVect::PolarVect()
{
    angle = 0;
    distance = 0;
}

PolarVect::PolarVect(int _angle, int _distance)
{
    angle = _angle;
    distance = _distance;
}

Point2D PolarVect::to2D()
{
    Point2D p;
    p.x = cos(angle) * distance;
    p.y = sin(angle) * distance;

    return p;
}

Steps PolarVect::toSteps()
{
    if (stepperNb == 4)
    {
        Steps s;

        // float ...
    }
}