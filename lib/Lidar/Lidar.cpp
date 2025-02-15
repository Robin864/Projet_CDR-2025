#include "Lidar.h"

Lidar::Lidar() {}

Lidar& Lidar::getInstance()
{
    static Lidar instance;
    return instance;
}

void Lidar::setup()
{
    Serial1.begin(230400, SERIAL_8N1, LIDAR_TX);
    LD06Lidar.init();
    LD06Lidar.setOffsetPosition(0, 0, gapRobotLidar);
    LD06Lidar.enableFiltering();
    LD06Lidar.setDistanceRange(minRangeDetection, maxRangeDetection);
    LD06Lidar.setIntensityThreshold(intensityThreshold);
}

void Lidar::setDistanceRange(int min, int max)
{
    LD06Lidar.setDistanceRange(min, max);
}

void Lidar::setDetectionDirection(float angle)
{
    float minAngle = angle - (detectionScope/2); // TODO: use mod 360
    float maxAngle = angle + (detectionScope/2);

    if (abs(minAngle) > 360 || abs(maxAngle) > 360)
        ERROR("wrong angle value");

    LD06Lidar.setAngleRange(minAngle, maxAngle);
}

void Lidar::setDetectionRotation()
{
    LD06Lidar.setAngleRange(0, 360);
}

bool Lidar::isDetected()
{
    if (LD06Lidar.readScan())
    {
        uint16_t detected = LD06Lidar.getNbPointsInScan();

        // DEBUG(detected);

        if (detected)
            return true;
        else
            return false;
    }
    return false;
}