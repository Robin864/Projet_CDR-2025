#include "Lidar.h"

Lidar::Lidar() {}

/**
 * @brief Gets the unique instance of the Lidar class (Singleton).
 * 
 * This method ensures that only one instance of the Lidar class exists and provides global access to it.
 * 
 * @return Lidar& Reference to the unique Lidar instance.
 */
Lidar& Lidar::getInstance()
{
    static Lidar instance;
    return instance;
}

/**
 * @brief Initializes the Lidar sensor with predefined settings.
 * 
 * This method configures the serial communication, initializes the Lidar module,
 * sets the position offset, enables filtering, and defines the detection range
 * and intensity threshold.
 */
void Lidar::setup()
{
    Serial1.begin(230400, SERIAL_8N1, LIDAR_TX);
    LD06Lidar.init();
    LD06Lidar.setOffsetPosition(0, 0, gapRobotLidar);
    LD06Lidar.enableFiltering();
    LD06Lidar.setDistanceRange(minRangeDetection, maxRangeDetection);
    LD06Lidar.setIntensityThreshold(intensityThreshold);
}

/**
 * @brief Sets the minimum and maximum detection range for the Lidar sensor.
 * 
 * @param min Minimum detection distance in millimeters.
 * @param max Maximum detection distance in millimeters.
 */
void Lidar::setDistanceRange(int min, int max)
{
    LD06Lidar.setDistanceRange(min, max);
}

/**
 * @brief Sets the detection direction of the Lidar sensor.
 * 
 * This method defines the angular range in which the Lidar detects objects,
 * based on a central angle and a predefined detection scope.
 * 
 * @param angle Central detection angle in degrees.
 *
 * @todo Improve error handling for out-of-range angles.
 */
void Lidar::setDetectionDirection(float angle)
{
    float minAngle = angle - (detectionScope/2); // TODO: use mod 360
    float maxAngle = angle + (detectionScope/2);

    if (abs(minAngle) > 360 || abs(maxAngle) > 360)
        ERROR("wrong angle value");

    LD06Lidar.setAngleRange(minAngle, maxAngle);
}

/**
 * @brief Enables full 360-degree detection for the Lidar sensor.
 * 
 * This method sets the Lidar's detection range to cover all directions.
 */
void Lidar::setDetectionRotation()
{
    LD06Lidar.setAngleRange(0, 360);
}

/**
 * @brief Checks if any object is detected by the Lidar sensor.
 * 
 * This method reads a new scan from the Lidar and determines if any points 
 * have been detected within the scan.
 * 
 * @return true if at least one point is detected, false otherwise.
 */
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