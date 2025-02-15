#include "Point2D.h"

Point2D::Point2D()
{
    x = 0;
    y = 0;
}

Point2D::Point2D(int _x)
{
    x = y = _x;
}

Point2D::Point2D(int _x, int _y)
{
    x = _x;
    y = _y;
}

Point2D Point2D::operator-(const Point2D& other)
{
    return Point2D(this->x - other.x, this->y - other.y);
}

Point2D Point2D::operator+(const Point2D& other)
{
    return Point2D(this->x + other.x, this->y + other.y);
}

Point2D Point2D::operator+=(const Point2D& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

PolarVect Point2D::toPolar()
{
    PolarVect p;
    p.angle = atan2(y, x);
    p.distance = sqrt(x*x + y*y);

    return p;
}

Steps Point2D::toSteps(float currentAngle)
{
    Steps base;

    PolarVect polar = this->toPolar();

    if (stepperNb == 4)
    {
        base.steps[0] = cos((polar.angle - currentAngle) + PI/4) * polar.distance; // TODO : check theorical polar.angle - currentAngle give the right pos
        base.steps[1] = cos((polar.angle - currentAngle) - PI/4) * polar.distance;
        base.steps[2] = sin((polar.angle - currentAngle) + PI/4) * polar.distance;
        base.steps[3] = -sin((polar.angle - currentAngle) - PI/4) * polar.distance;
    }

    return base;
}