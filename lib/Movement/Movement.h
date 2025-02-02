#pragma once

#include <cmath>
#include <Arduino.h>
#include <AccelStepper.h>

#include "UniBoardV4Def.h"

#include "Lidar.h"
#include "DoubleMap.h"
#include "Point2D.h"
#include "PolarVect.h"

const double ACCEL = 500;
const double SPEED = 1000;

class Movement
{
private:
    Lidar& lidar = Lidar::getInstance();
    Point2D currentPos, liveCurrentPos;
    float maxSteps, currentRotation, progress;
    const int uStep = 8;
    int maxStepsIndex;
    DoubleMap<AccelStepper> stepper;
    void rotateBy(float angle);

public:
    Movement();
    void setup();
    void moveTo(Point2D target);
    void moveBy(Point2D target);
    void rotateTo(float angle);
    void rotateLeftBy(float angle);
    void rotateRightTo(float angle);
    void run();
    void updateProgress();
    bool isArrived();
    Point2D getCurrentPos();
};