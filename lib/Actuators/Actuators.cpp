#include "Actuators.h"

Actuators::Actuators()
{

}

void Actuators::setup()
{
    Wire.begin(PIN::I2C::SDA, PIN::I2C::SCL);

    pwm = Adafruit_PWMServoDriver(pwmAddress, Wire);
    pwm.begin();
    pwm.setOscillatorFrequency(oscillatorFreq);
    pwm.setPWMFreq(servoFreq);
}

void Actuators::grabCan(int side)
{
    if (!cans[side])
    {
        switch (side)
        {
        case Left:
            // Down
            pwm.setPWM(Leftside_LeftLifter, 0, 400);
            pwm.setPWM(Leftside_RightLifter, 0, 400);
            delay(0); // Calculate time to move both servos

            // Orientate
            pwm.setPWM(Leftside_LeftOrienter, 0, 400);
            pwm.setPWM(Leftside_RightOrienter, 0, 400);
            delay(0); // Calculate time to move both servos

            // Grab
            pwm.setPWM(Leftside_LeftGraber, 0, 400);
            pwm.setPWM(Leftside_RightGraber, 0, 400);
            delay(0); // Calculate time to move both servos

            // Lift
            pwm.setPWM(Leftside_LeftLifter, 0, 150);
            pwm.setPWM(Leftside_RightLifter, 0, 150);
            delay(0); // Calculate time to move both servos 
            break;

        case Front:
            // Down
            pwm.setPWM(Frontside_Lift, 0, 400);
            delay(0);

            // Grab
            pwm.setPWM(Frontside_LeftGraber, 0, 400);
            pwm.setPWM(Frontside_RightGraber, 0, 400);
            delay(0); // Calculate time to move both servos

            // Lift
            pwm.setPWM(Frontside_Lift, 0, 150);
            delay(0);
            break;

        default:
            break;
        }

        cans[side] = true;
    }
}

void Actuators::ungrabCan(int side)
{
    if (cans[side])
    {
        switch (side)
        {
        case Left:
            // Down
            pwm.setPWM(Leftside_LeftLifter, 0, 400);
            pwm.setPWM(Leftside_RightLifter, 0, 400);
            delay(0); // Calculate time to move both servos

            // UnGrab
            pwm.setPWM(Leftside_LeftGraber, 0, 150);
            pwm.setPWM(Leftside_RightGraber, 0, 150);
            delay(0); // Calculate time to move both servos

            // Orientate
            pwm.setPWM(Leftside_LeftOrienter, 0, 150);
            pwm.setPWM(Leftside_RightOrienter, 0, 150);
            delay(0); // Calculate time to move both servos

            // Lift
            pwm.setPWM(Leftside_LeftLifter, 0, 150);
            pwm.setPWM(Leftside_RightLifter, 0, 150);
            delay(0); // Calculate time to move both servos 
            break;

        case Front:
            // Down
            pwm.setPWM(Frontside_Lift, 0, 400);
            delay(0);

            // Grab
            pwm.setPWM(Frontside_LeftGraber, 0, 150);
            pwm.setPWM(Frontside_RightGraber, 0, 150);
            delay(0); // Calculate time to move both servos

            // Lift
            pwm.setPWM(Frontside_Lift, 0, 150);
            delay(0);
            break;

        default:
            break;
        }

        cans[side] = false;
    }
}

void Actuators::grabPlank()
{
    if (!planks)
    {
        // Down
        pwm.setPWM(Rightside_Lifter, 0, 400);
        delay(0);

        // Grab (pump)
        pwm.setPWM(Rightside_LeftPump, 0, 400);
        pwm.setPWM(Rightside_RightPump, 0, 400);
        delay(0);

        // Lift
        pwm.setPWM(Rightside_Lifter, 0, 150);
        delay(0);

        planks = true;
    }
}

void Actuators::ungrabPlank()
{
    if (!planks)
    {
        // Down
        pwm.setPWM(Rightside_Lifter, 0, 400);
        delay(0);

        // Grab (pump)
        pwm.setPWM(Rightside_LeftPump, 0, 150);
        pwm.setPWM(Rightside_RightPump, 0, 150);
        delay(0);

        // Lift
        pwm.setPWM(Rightside_Lifter, 0, 150);
        delay(0);
        
        planks = true;
    }
}

void Actuators::dropBanner()
{
    if (banner)
    {
        // Down 
        pwm.setPWM(Backside_Lifter, 0, 400);
        delay(0);
        
        banner = false;
    }
}