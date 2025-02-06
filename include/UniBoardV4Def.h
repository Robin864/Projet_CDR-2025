/*
    Based on https://raw.githubusercontent.com/Unimakers/CDR-2024-FIRMWARE/main/CDR2024%20BASE/lib/Define/UniBoardDef.h
    Updated 13/04/2024
*/

#ifndef UNIBOARDV4DEF_H
#define UNIBOARDV4DEF_H

namespace PIN
{
    namespace Inputs
    {
        constexpr int
        TIR = 6,
        btn1 = 7,
        btn2 = 48;
    } // namespace Inputs

    namespace Steppers
    {
        constexpr int STEP[4] = {
            10, // STEP1
            46, // STEP2
            13, // STEP3
            21, // STEP4
        };

        constexpr int DIR[4] = {
            9, // DIR1
            3, // DIR2
            12, // DIR3
            14, // DIR4
        };

        constexpr int EN = 11;
    } // namespace Steppers
    
    namespace Lidar
    {
        constexpr int
            LIDAR_TX = 18,
            LIDAR_RX = 17,
            LIDAR_PWM = 8;
    } // namespace Lidar

    namespace I2C
    {
        constexpr int
            SDA = 4,
            SCL = 5;
    } // namespace I2C
    
    namespace Nappe
    {
        constexpr int
            NAPPE1 = 45,
			NAPPE2 = 40,
			NAPPE3 = 41,
			NAPPE4 = 42,
			NAPPE5 = 39,
			NAPPE6 = 38,
			NAPPE7 = 1,
			NAPPE8 = 2;
    } // namespace Nappe
    
} // namespace PIN

static constexpr int TEAM_PIN = PIN::Inputs::btn1;
static constexpr int INIT_PIN = PIN::Inputs::btn2;
static constexpr int TIR_PIN = PIN::Inputs::TIR;

#endif