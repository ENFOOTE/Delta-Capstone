// File: CapacitiveSensor.h
// Programmer 1: David S. Vasquez
// Programmer 2: Jorge Villalobos
// Programmer 3: Eric Foote
// Date: January 7, 2017
// Information: This header file will be used for the capacitive sensor. The
// main purpose of this header file is to determine if there is an capacitive
// signal directly below the robot. If there is a voltage below the robot
// at the current square foot.

#ifndef CAPACITIVESENSOR_H
#define CAPACITIVESENSOR_H

// Important information about this class: The 'float voltageRMS' variable
// will store the float variable that is recorded by the capacitive sensor. The analog
// to digital converter on the Arduino board. However, this code needs some
// updates. I (David) needs to research the ADC. The 'CapacitiveSensor' function is a
// constructor. The 'getVoltage' function stores the RMS voltage into the 'voltageRMS'
// variable. The 'checkRange' function returns a bool variable, true equals capacitive voltage
// has been detected, false equals EMF voltage not detected.
class CapacitiveSensor
{
    private:
        float voltageRMS;

    public:
        CapacitiveSensor();
        void getVoltage();
        bool checkRange();

};

#endif
