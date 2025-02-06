#include "Movement.h"

Movement::Movement()
{
    for (int i = 0; i < stepperNb; i++)
        stepper[i] = AccelStepper(AccelStepper::DRIVER, PIN::Steppers::STEP[i], PIN::Steppers::DIR[i]);
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
    targetPosRelative = targetRelative;
    targetPosAbsolute = currentPos - targetPosRelative;
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

    run();
}

void Movement::rotateTo(float angle)
{
    if (angle > 360)
        angle = fmod(angle, 360); // dividend, divisor

    float command = currentRotation - angle;
    command = currentRotation - command;

    rotateBy(command); // TODO: evaluate minimal angle
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

    stepper[FrontRight].move(-angle * uStep);
    stepper[RearRight].move(-angle * uStep);
    stepper[FrontLeft].move(angle * uStep);
    stepper[RearLeft].move(angle * uStep);

    do
    {
        for (int i = 0; i < stepperNb; i++)
            stepper[i].run(); // When rotate, position must not be updated
    } while (!isArrived());

    currentRotation += angle;
}

void Movement::rotateLeftBy(float angle)
{
    rotateBy(-angle);
}

void Movement::rotateRightBy(float angle)
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
            stop();
        }
    } while (!isArrived());
    
    // TODO : Estimate drifting using liveCurrentPos and currentPos
    // Correct it if possible
    liveCurrentPos = currentPos;
}

void Movement::stop()
{
    for (int i = 0; i < stepperNb; i++)
        stepper[i].stop();

    delay(1000);

    moveTo(targetPosAbsolute);
}

void Movement::fullstop()
{
    digitalWrite(PIN::Steppers::EN, HIGH);
    for (;;);
}

void Movement::updateProgress()
{
    progress = stepper[maxStepsIndex].currentPosition() / maxSteps; // Percentage
    
    liveCurrentPos = {
        currentPos.x + targetPosRelative.x * progress,
        currentPos.y + targetPosRelative.y * progress
    };
}

bool Movement::isArrived()
{
    for (int i = 0; i < stepperNb; i++)
        if (stepper[i].distanceToGo() != 0)
            return false;

    return true;
}

Point2D Movement::getCurrentPos()
{
    return liveCurrentPos;
}