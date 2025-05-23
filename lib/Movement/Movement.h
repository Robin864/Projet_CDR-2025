#pragma once

#include <cmath>
#include <Arduino.h>
#include <AccelStepper.h>

#include "UniBoardV4Def.h"

#include "Lidar.h"
// #include "DoubleMap.h"
#include "Point2D.h"
#include "PolarVect.h"

#include "config.h"
using namespace config::Movement;

class Movement
{
private:
    bool isRotation;
    int maxStepsIndex;

    double maxSteps, currentRotation, progress;
    double last[3][stepperNb];

    Lidar& lidar = Lidar::getInstance();
    AccelStepper stepper[stepperNb];
    Point2D targetPosRelative, targetPosAbsolute, currentPos, liveCurrentPos;

    void rotateBy(float angle);
    void updateProgress();

public:
    Movement();
    void setup();
    void init();

    void moveTo(Point2D target);
    void moveBy(Point2D target);

    void rotateTo(float angle);
    void rotateLeftBy(float angle);
    void rotateRightBy(float angle);

    void run();
    void dryRun();
    void stop();
    void fullstop();
    
    bool isArrived();
    Point2D getCurrentPos();
};