#pragma once

#include <Arduino.h>
#include <AccelStepper.h>

#include "UniBoardV4Def.h"

#include "types/DoubleMap.h"
#include "types/Point2D.h"
#include "types/PolarVect.h"

const double ACCEL = 500;
const double SPEED = 1000;

class Movement
{
private:
    Point2D currentPos, liveCurrentPos;
    float maxSteps, currentRotation, progress;
    int maxStepsIndex;
    DoubleMap<AccelStepper> stepper;

public:
    Movement();
    void setup();
    void moveTo(Point2D target);
    void moveBy(Point2D target);
    void rotateTo(float angle);
    void rotateBy(float angle);
    void run();
    void updateProgress();
    bool isArrived();
    Point2D getCurrentPos();
};