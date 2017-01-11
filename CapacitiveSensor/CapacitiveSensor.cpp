// File: CapacitiveSensor.cpp
// Programmer 1: David S. Vasquez
// Programmer 2: Jorge Villalobos
// Programmer 3: Eric Foote
// Date: January 11, 2017
// Information: This implementation file will be used for the capacitive sensor. The
// main purpose of this header file is to determine if there is an capacitive
// signal directly below the robot. If there is a voltage below the robot
// at the current square foot.

#include <iostream>
#include "CapacitiveSensor.h"

using namespace std;

// This is a constructor.
CapacitiveSensor::CapacitiveSensor()
{
    // This statement initializes a default value for the voltageRMS value, the
    // the default value is 0 volts.
    voltageRMS = 0.0;
}

// This function will use the analog to digital converter on the Arduino board. I (David)
// need to determine how to use the ADC on the Arduino board.
CapacitiveSensor::getVoltage();
{
    float inputVoltage = 0.0;

    // Here is some code on enabling the ADC unit.

    voltageRMS = inputVoltage;
}

CapacitiveSensor::returnVoltage();
{
    return voltageRMS;
}

CapacitiveSensor::checkRange();
{
    bool voltageDetected = false;

    // This if statement has a minimum voltage and a maximum voltage. However, these values
    // are initially subjective to testing. Adjust the values after running tests on the course
    // map.
    if(voltageRMS >= 1.0 || voltageRMS <= 5.0)
    {
        voltageDetected = true;
    }

    return voltageDetected;
}



