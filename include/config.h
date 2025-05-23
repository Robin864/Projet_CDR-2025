#ifndef CONFIG_H
#define CONFIG_H

namespace config
{
    namespace Movement
    {
        inline constexpr int uStep = 8;
        inline constexpr int stepperNb = 4;

        inline constexpr double ACCEL = 500;
        inline constexpr double SPEED = 1000;

        enum stepperKey
        {
            FrontRight,
            RearRight,
            FrontLeft,
            RearLeft,
        };

        enum params
        {
            speed,
            accel,
            steps,
        };

        enum rotation
        {
            quarter = 90,
            half = 180,
        };
    }
    
    namespace Actuators
    {
        inline constexpr int pwmAddress = 0x40;
        inline constexpr int oscillatorFreq = 25000000;
        inline constexpr int servoFreq = 50;

        enum Sides
        {
            Right,
            Left,
            Front,
            Back
        };
    }

    namespace Lidar
    {

    }

    namespace General
    {

    }
    
}

#endif