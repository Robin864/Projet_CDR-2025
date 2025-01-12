#include "Lidar.h"

void Lidar::setup()
{
    Serial1.begin(230400, SERIAL_8N1, LIDAR_TX);
    lidar.init();
    lidar.setOffsetPosition(0, 0, gapRobotLidar);
    lidar.enableFiltering();
    lidar.setDistanceRange(minRangeDetection, maxRangeDetection);
    lidar.setIntensityThreshold(intensityThreshold);
}

void Lidar::setDistanceRange(int min, int max)
{
    lidar.setDistanceRange(min, max);
}

void Lidar::setDetectionDirection(float angle)
{
    float minAngle = angle - (detectionScope/2);
    float maxAngle = angle + (detectionScope/2);

    if (abs(minAngle) > 360 || abs(maxAngle) > 360)
        ERROR("wrong angle value");

    lidar.setAngleRange(minAngle, maxAngle);
}

bool Lidar::isDetected(float angle)
{
    setDetectionDirection(angle);

    if (lidar.readScan())
    {
        uint16_t detected = lidar.getNbPointsInScan();

        // DEBUG(detected);

        if (detected)
            return true;
        else
            return false;
    }
    return false;
}