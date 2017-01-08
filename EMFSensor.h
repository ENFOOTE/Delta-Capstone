// File: EMFSensor.h
// Programmer 1: David S. Vasquez
// Programmer 2: Jorge Villalobos
// Programmer 3: Eric Foote
// Date: January 7, 2017
// Information: This header file will be used for the EMF sensor. The
// main purpose of this header file is to determine if there is an EMF
// signal directly below the robot. If there is a voltage below the robot
// at the current square foot.

#ifndef EMFSENSOR_H
#define EMFSENSOR_H

// Important information about this class: The 'float voltageRMS' variable
// will store the float variable that is recorded by the EMFSensor. The analog
// to digital converter on the Arduino board. However, this code might need some
// updates. I (David) needs to research the ADC. The 'EMFSensor' function is a
// constructor. The 'getVoltage' function stores the RMS voltage into the 'voltageRMS'
// variable.
class EMFSensor
{
    private:
        float voltageRMS;

    public:
        EMFSensor();
        void getVoltage();
        bool checkRange();

};

