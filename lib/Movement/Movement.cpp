#include "Movement.h"

using namespace PIN::Steppers;

Movement::Movement()
{
    stepper.append("fr", AccelStepper(AccelStepper::DRIVER, STEP1, DIR1));
    stepper.append("rr", AccelStepper(AccelStepper::DRIVER, STEP2, DIR2));
    stepper.append("fl", AccelStepper(AccelStepper::DRIVER, STEP3, DIR3));
    stepper.append("rl", AccelStepper(AccelStepper::DRIVER, STEP4, DIR4));
}

void Movement::setup()
{
    for (int i = 0; i < stepperNb; i++)
    {
        stepper[i].setAcceleration(ACCEL);
        stepper[i].setMaxSpeed(ACCEL);
    }
}

void Movement::moveTo(Point2D targetAbsolute)
{
    moveBy(targetAbsolute - currentPos);
}

void Movement::moveBy(Point2D targetRelative)
{
    Steps base = targetRelative.toSteps(currentRotation);
    float detectionDirection = targetRelative.toPolar().angle;
    lidar.setDetectionDirection(detectionDirection);

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

    float scalers[stepperNb],
        speed[stepperNb],
        accel[stepperNb];

    for (int i = 0; i < stepperNb; i++)
    {
        scalers[i] = absSteps[i] / maxSteps;
        speed[i] = SPEED * scalers[i];
        accel[i] = ACCEL * scalers[i];
    
        stepper[i].setMaxSpeed(speed[i]);
        stepper[i].setAcceleration(accel[i]);
        stepper[i].setCurrentPosition(0);
        stepper[i].move(base.steps[i]);
    }

    run();
}

void Movement::rotateTo(float angle)
{
    if (angle > 360)
        angle = fmod(angle, 360); // dividend, divisor

    float command = currentRotation - angle;
    command = currentRotation - command;

    rotateBy(command); // TODO: evaluate minimal distance
}

void Movement::rotateBy(float angle)
{
    if (angle > 360)
        angle = fmod(angle, 360);
        
    for (int i = 0; i < stepperNb; i++)
    {
        stepper[i].setMaxSpeed(SPEED);
        stepper[i].setAcceleration(ACCEL*2);
        stepper[i].setCurrentPosition(0);
    }

    stepper["fr"].move(-angle * uStep);
    stepper["rr"].move(-angle * uStep);
    stepper["fl"].move(angle * uStep);
    stepper["rl"].move(angle * uStep);

    for (int i = 0; i < stepperNb; i++)
        stepper[i].run();
}

void Movement::rotateLeftBy(float angle)
{
    rotateBy(-angle);
}

void Movement::rotateRightTo(float angle)
{
    rotateBy(angle);
}

void Movement::run()
{
    do
    {
        if (!lidar.isDetected())
        {
            for (int i = 0; i < stepperNb; i++)
                stepper[i].run();

            updateProgress();
        }
        else
        {
            // stop(); // TODO : stop implementation
        }
        liveCurrentPos; // TODO : Progress implementation
    } while (!isArrived());
}

bool Movement::isArrived()
{
    for (int i = 0; i < stepperNb; i++)
        if (stepper[i].distanceToGo() != 0)
            return false;

    return true;
}