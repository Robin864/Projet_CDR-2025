#include "Movement.h"

/**
 * @brief Constructor for the Movement class.
 *
 * Initializes the Movement object by setting up stepper motors.
 * Iterates over the number of steppers and initializes each one using the AccelStepper library.
 * Each stepper is configured with its respective step and direction pins.
 *
 * @note This constructor prepares the stepper motors for use in movement operations.
 */
Movement::Movement()
{
    for (int i = 0; i < stepperNb; i++)
        stepper[i] = AccelStepper(AccelStepper::DRIVER, PIN::Steppers::STEP[i], PIN::Steppers::DIR[i]);
}

/**
 * @brief Sets up the movement system.
 *
 * Configures each stepper motor by setting its acceleration and maximum speed.
 * Iterates over the number of steppers and applies the same settings to each one.
 *
 * @note This method should be called to initialize the movement system before any movement operations are performed.
 */
void Movement::setup()
{
    for (int i = 0; i < stepperNb; i++)
    {
        stepper[i].setAcceleration(ACCEL);
        stepper[i].setMaxSpeed(ACCEL);
    }
}

/**
 * @brief Initializes the movement system and positions the robot at the starting point.
 *
 * Resets each stepper motor's current position to zero and sets their maximum speed and acceleration.
 * Moves specific steppers to a predefined position and performs a dry run to ensure proper initialization.
 * Sets the robot's current position and moves it to a specified starting point.
 *
 * @note This method prepares the robot for operation by setting initial positions and performing initial movements.
 * @todo Set the robot's offset to account for any initial position adjustments.
 */
void Movement::init()
{
    for (int i = 0; i < stepperNb; i++)
    {
        stepper[i].setCurrentPosition(0);
        stepper[i].setMaxSpeed(SPEED);
        stepper[i].setAcceleration(ACCEL);
    }

    stepper[FrontLeft].move(2200);
    stepper[RearRight].move(2200);
    dryRun();
    
    currentPos = {0, 0}; // TODO: set robot's offset
    moveTo(Point2D(150));
}

/**
 * @brief Moves the robot to an absolute target position.
 *
 * Calculates the relative movement required to reach the specified absolute position
 * from the current position and calls `moveBy` to execute the movement.
 *
 * @param targetAbsolute The absolute target position to move to, expressed as a Point2D.
 *
 * @note This method simplifies moving to an absolute position by leveraging the relative movement logic.
 */
void Movement::moveTo(Point2D targetAbsolute)
{
    moveBy(targetAbsolute - currentPos);
}

/**
 * @brief Moves the robot by a relative target position.
 *
 * Calculates the necessary steps to move the robot to a position relative to its current position.
 * Adjusts the speed and acceleration of each stepper motor based on the calculated steps.
 * Sets the detection direction for the lidar and initiates the movement.
 *
 * @param targetRelative The relative target position to move to, expressed as a Point2D.
 *
 * @note This method handles relative movements and adjusts motor parameters to ensure smooth and coordinated motion.
 */
void Movement::moveBy(Point2D targetRelative)
{
    isRotation = false;
    targetPosRelative = targetRelative;
    targetPosAbsolute = currentPos - targetPosRelative;
    Steps base = targetRelative.toSteps(currentRotation);
    
    float detectionDirection = targetRelative.toPolar().angle;
    
    float absSteps[stepperNb];
    
    for (int i = 0; i < stepperNb; i++)
    absSteps[i] = abs(base.steps[i]);
    
    maxSteps = absSteps[0];
    for (int i = 0; i < stepperNb; i++)
    if (absSteps[i] > maxSteps)
    {
        maxSteps = absSteps[i];
        maxStepsIndex = i;
    }
    
    float scalers[stepperNb];
    
    for (int i = 0; i < stepperNb; i++)
    {
        scalers[i] = absSteps[i] / maxSteps;
        
        last[speed][i] = SPEED * scalers[i];
        last[accel][i] = ACCEL * scalers[i];
        last[steps][i] = base.steps[i];
        
        stepper[i].setMaxSpeed(last[speed][i]);
        stepper[i].setAcceleration(last[accel][i]);
        stepper[i].setCurrentPosition(0);
        stepper[i].move(base.steps[i]);
    }
    
    lidar.setDetectionDirection(detectionDirection);
    run();
}

/**
 * @brief Rotates the robot to a specified target rotation angle.
 *
 * @param angle The target rotation angle in degrees (0-360).
 *
 * @note If the input angle exceeds 360 degrees, it is reduced modulo 360 to ensure accurate calculation.
 *
 * @todo Evaluate and implement minimal rotation increment.
 */
void Movement::rotateTo(float angle)
{
    if (angle > 360)
        angle = fmod(angle, 360); // dividend, divisor

    float command = currentRotation - angle;
    command = currentRotation - command;

    rotateBy(command); // TODO: evaluate minimal angle
}

/**
 * @brief Rotates the robot by a specified target rotation angle.
 *
 * @param angle The target rotation angle in degrees (0-360).
 *
 * @note If the input angle exceeds 360 degrees, it is reduced modulo 360 to ensure accurate calculation.
 */
void Movement::rotateBy(float angle)
{
    isRotation = true;
    if (angle > 360)
        angle = fmod(angle, 360);
        
    for (int i = 0; i < stepperNb; i++)
    {
        stepper[i].setMaxSpeed(SPEED);
        stepper[i].setAcceleration(ACCEL*2);

        stepper[i].setCurrentPosition(0);
    }

    stepper[FrontRight].move(-angle * uStep);
    stepper[RearRight].move(-angle * uStep);
    stepper[FrontLeft].move(angle * uStep);
    stepper[RearLeft].move(angle * uStep);

    lidar.setDetectionRotation();
    run();

    currentRotation += angle;
}

/**
 * @brief Rotates the robot to the left by a specified target rotation angle.
 *
 * @param angle The target rotation angle in degrees (0-360).
 */
void Movement::rotateLeftBy(float angle)
{
    rotateBy(-angle);
}

/**
 * @brief Rotates the robot to the right by a specified target rotation angle.
 *
 * @param angle The target rotation angle in degrees (0-360).
 */
void Movement::rotateRightBy(float angle)
{
    rotateBy(angle);
}

/**
 * @brief Runs the movement loop, continuously checking for obstacles and updating progress.
 *
 * @todo Implement drifting correction using liveCurrentPos and currentPos.
 */
void Movement::run()
{
    do
    {
        if (!lidar.isDetected())
        {
            for (int i = 0; i < stepperNb; i++)
                stepper[i].run();

            if (!isRotation)
                updateProgress();
        }
        else
        {
            stop();
        }
    } while (!isArrived());
    
    // TODO : Estimate drifting using liveCurrentPos and currentPos
    // Correct it if possible
    if (!isRotation)
        liveCurrentPos = currentPos;
}

/**
 * @brief Runs a dry run of the movement loop, simulating forward motion without obstacle detection.
 *
 * @note This function is equivalent to run() and should be used for testing purposes.
 */
void Movement::dryRun()
{
    do
    {
        for (int i = 0; i < stepperNb; i++)
            stepper[i].run();
    } while (!isArrived());
    
}

/**
 * @brief Stops the movement by shutting down all stepper motors.
 */
void Movement::stop()
{
    for (int i = 0; i < stepperNb; i++)
        stepper[i].stop();
}

/**
 * @brief Immediately shuts down the movement by powering off all stepper motors.
 *
 * @note This function will block indefinitely until manually interrupted or terminated.
 */
void Movement::fullstop()
{
    for (int i = 0; i < stepperNb; i++)
        stepper[i].stop();
    digitalWrite(PIN::Steppers::EN, HIGH);
    for (;;);
}

/**
 * @brief Updates the movement progress based on the stepper motor's position.
 */
void Movement::updateProgress()
{
    progress = stepper[maxStepsIndex].currentPosition() / maxSteps; // Percentage
    
    liveCurrentPos = {
        currentPos.x + targetPosRelative.x * progress,
        currentPos.y + targetPosRelative.y * progress
    };
}

/**
 * @brief Checks if the movement has arrived at its destination.
 *
 * @return true if all stepper motors have reached their target position, false otherwise.
 */
bool Movement::isArrived()
{
    for (int i = 0; i < stepperNb; i++)
        if (stepper[i].distanceToGo() != 0)
            return false;

    return true;
}

/**
 * @brief Returns the current position of the movement.
 *
 * @return The current position of the movement, represented as a Point2D structure.
 */
Point2D Movement::getCurrentPos()
{
    return liveCurrentPos;
}