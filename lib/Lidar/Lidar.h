#pragma once

#include "ld06.h"
#include "UniBoardV4Def.h"
#include "utils.h"

using namespace PIN::Lidar;

class Lidar
{
private:
    LD06 lidar;
    int minRangeDetection = 150, maxRangeDetection = 400; // mm
    int intensityThreshold = 225; // Max = 255, depends of room light
    int detectionScope = 90;
    float gapRobotLidar = 0; // Gap between robot's forward and lidar's forward in degrees

public:
    void setup();
    void setDistanceRange(int minimum = 0, int maximum = 12000);
    void setDetectionDirection(float angle);
    bool isDetected(float angle);
};