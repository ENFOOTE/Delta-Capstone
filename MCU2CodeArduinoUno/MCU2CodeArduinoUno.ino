// EE4390 EE Design I and EE4391 EE Design II
// Date created: December 01, 2016 
// Programmer One: David S Vasquez
// Programmer Two: Geovanni Hernandez
// Programmer Three: Eric Foote
// Programmer Four: Jorge Villalobos
// Libraries: "NewPing.h" is used for the UltraSonic Distance Sensor, <SPI.h> 
// is used for the SPI communication between the Arduino boards. "EMFSensor.h" 
// is used for the custom made four EMF sensors, these sensors capture and amplify
// a 60 Hz signal. The "CapacitiveSensor.h" is used for capturing the unique 
// voltage of the insulation or dead-end tunnel. The "ArrayLED.h" library is 
// used to light individual LEDs on the LED matrix.
// Information: This is the master code program for the Arduino Uno
// board (second board MC2). This program will be used by all the 
// hardware connected to this board. This program communicate with 
// the Mega board. 

#include "NewPing.h"
// #include "EMFSensor.h"
// #include "ArrayLED.h"

#include <SPI.h>

// This integer variable will be used by the switch statement located in
// the SPI interrupt function.
volatile int switchCommand = 0;

// This declaration and initialization is for the Slave Select Pin. The
// SPI library will automatically set the other SPI Pins.
int slavePin = 10;

// The variable called 'US_ROUNDTRIP_MM' was created specifically so 
// the sensor would return distance values in millimeters. Normally, 
// the sensor would return values in centimeters.
#define US_ROUNDTRIP_MM 5.7

// These are the constructors for the UltraSonic Distance Sensors.
NewPing sonarN(TRIGGER_PIN = 23, ECHO_PIN = 22, MAX_DISTANCE = 200);
NewPing sonarW(TRIGGER_PIN = 25, ECHO_PIN = 24, MAX_DISTANCE = 200);
NewPing sonarS(TRIGGER_PIN = 27, ECHO_PIN = 26, MAX_DISTANCE = 200);
NewPing sonarE(TRIGGER_PIN = 29, ECHO_PIN = 28, MAX_DISTANCE = 200);

// These functions will return a True or False bool value depending on
// if an obstacle is detected on the field in front of the corresponding
// Ultrasonic sensor.
bool read_ObstacleN();
bool read_ObstacleW();
bool read_ObstacleS();
bool read_ObstacleE();

// This integer variable will be used to store the movement direction.
int moveDirection;

// This variable will be used to store an integer value sent by SPI from
// the master. This value starts the entire sensor LED algorithm.
int startAlgorithmSensorLED;

/*
// This function determines the configuration of the extension cable.
int cableConfig(float, float, float, float);

// These four constructors are for the four EMF Sensors. The variable
// name represents the corresponding EMF by using these labels: N=North, 
// S=South, W=West, and E=East.
EMFSensor sensorN;
EMFSensor sensorS;
EMFSensor sensorW;
EMFSensor sensorE;

// This integer variable will be used to store a value that represents the
// current EMF cable configuration that is detected by the four EMF sensors. Int value
// 12 = config W-E, 13 = config N-S, 14 = config N-E, 15 = config S-E, 16 = config W-S,
// 17 = config N-W. The value will be used to communicate to the master via SPI.
int EMF_SPI;

// This integer variable will be used to store a value that represents whether or
// not there is an obstacle in the upcoming foot by foot square in the direction of
// movement of the robot. Integer value 18 = Obstacle detected, integer value 19 = 
// obstacle not detected.
int obstacleSPI;

// These string variables will be used for the LED features. The 'strLoc' is the current 
// location of the robot, the 'colorLEDcurr' is the correct color per the output of the
//  sensors.
string strLoc;
string colorLEDcurr;

// This is the class object instance of the LED using Jorge's LED code.
ArrayLED mapObject;
*/

// This void function is used to setup important features
// of the Arduino microprocessor board.
void setup() {
  Serial.begin(115200);

  // This code enables master in and slave out.
  pinMode(MISO, OUTPUT);

  // This code enables SPI in slave mode.
  SPCR |= _BV(SPE);

  // This code enables SPI interrupts.
  SPCR |= _BV(SPIE);

  // The reason for initializing this integer variable is to ensure that sensor-LED
  // algorithm does not execute until the SPI command.
  startAlgorithmSensorLED = 0;

  moveDirection = 0;
}

// This function is the SPI interrupt routine function.
ISR(SPI_STC_vect) {
  // The function will use a switch with command variable. The command variable
  // will determine which values are sent to the master.
  int incomingInt = SPDR;

  switch(switchCommand) {
    case 0:
      switchCommand = incomingInt;
      SPDR = 0;
      break;
    case 1:
      startAlgorithmSensorLED = incomingInt;
      // switchCommand = 0;
      break;
    case 2:
      moveDirection = switchCommand;
      break;
    case 3:
      moveDirection = switchCommand;
      break;
    case 4:
      moveDirection = switchCommand;
      break;
    case 5:
      moveDirection = switchCommand;
      break;
    // case 6:    
    // case 7:
    // case 8:
    // case 9:
    // case 10:
    // case 11:
    // case 12:
    // case 13:
    // case 14:
  }
}

// This void function acts just like the main function.
void loop() {
  // This if statement will ensure that if SPI isn't active (slave select is HIGH),
  // then clear the current command for the switch (variable switchCommand).
  if(digitalRead(slavePin) == HIGH) {
    switchCommand = 0;
  }
  
  // This if statement will execute the sensor algorithm. The 'startAlgorithmSensorLED'
  // will be initialized by a SPI command that is sent by the master MCU. 
  if(startAlgorithmSensorLED == 1) {

    // This variable will be used to store whether or not there is an obstacle in
    // the upcoming one foot square section. It will be initialized with the return
    // value of one of the four bool read_Obstacle functions. 
    bool scan4Obstacle;

    /*
    // These four bool variables will be used by the corresponding EMF sensor. These 
    // bool variables will store a true if any of the four EMF sensors detects an 
    // EMF sensor. The false value represents that neither of the four EMF sensors
    // have detected an EMF signal. These bool variables are initialized by the 
    // return value of the 'checkRange' function used in the EMF sensor class. 
    bool voltDectN;
    bool voltDectE;
    bool voltDectS;
    bool voltDectW;

    // This variable will be used to communicate to the MCU that drives the motors.
    int currentCableConfig = 0;
    */

    // These four if statements will execute depending on the next immediate direction
    // that the robot will take. This direction will be determined by receiving a SPI
    // integer command from the master board. Int value 2 = move north, int value 3 =
    // move west, int value 4 = move south, int value 5 = move east.   
    if(moveDirection == 2) {
      scan4Obstacle = read_ObstacleN();
    }
    if(moveDirection == 3) {
      scan4Obstacle = read_ObstacleW();
    }
    if(moveDirection == 4) {
      scan4Obstacle = read_ObstacleS();
    }
    if(moveDirection == 5) {
      scan4Obstacle = read_ObstacleE();
    }

    // These if/else statements will communicate to the master MCU on whether or not
    // there is an obstacle in the next foot by foot square. Integer value 12 = obstacle
    // was detected, value 13 = obstacle not detected.  
    if(scan4Obstacle == true) {
      switchCommand = 13;
    }
    else {
      switchCommand = 14;
    }

    if(startEMF == 6) {
      /*
      voltDectN = false;
      voltDectE = false;
      voltDectS = false;
      voltDectW = false;
    
      // This code uses all four EMF sensors to scan for a voltage. This voltage should
      // a single float value.
      sensorN.getVoltage();
      sensorE.getVoltage();
      sensorS.getVoltage();
      sensorW.getVoltage();

      // These initialization statements return a true or false bool value depending on if the 
      // detected voltage is within a certain range. The range is determined during testing on
      // the field.
      voltDectN = sensorN.checkRange();
      voltDectE = sensorE.checkRange();
      voltDectS = sensorS.checkRange();
      voltDectW = sensorW.checkRange();

      // This if/statement determines whether or not any of the four EMF sensors detects a
      // voltage. 
      if(voltDectN == true || voltDectE == true || voltDectS == true || voltDectW == true) {
        // I (David) need to include the code for lighting the LED array at this point in
        // code. Look at Jorge's implementation code and add it here.

        // The following code will determine if the extension cable is running in a straight 
        // line or if there is a bend at this particular square.
        legendValueSPI = cableConfig(sensorN, sensorE, sensorS, sensorW);

        // Send the SPI code value to the master, use the 'legendValueSPI' int variable.
      }
      */
    }
  }
}


// This function is used to determine if there is an obstacle on the field direction
// north of the robot. 
bool read_ObstacleN() {
  // This variable stores the values calculated by the UltraSonic
  // hardware. In addition, the variable is initialized using the 
  // ping function from the NewPing class.
  float sensorData = sonarN.ping();

  // This bool variable will be used to return a true value if the
  // the object is detected and a false variable no objectt is detected.
  bool objDetected;

  // This variable is used to store the actual distance value. 
  float objDist;
  objDist = sensorData / US_ROUNDTRIP_MM;

  // This if statement uses a range in millimeters to determine if there
  // is an object in the next square. The range and the sensor needs to 
  // be tested and verified. 
  if(objDist >= 50 || objDist <= 305) {
    return true;
  }
  else {
    return false;
  }
}

// This function is used to determine if there is an obstacle on the field direction
// west of the robot. 
bool read_ObstacleW() {
  // This variable stores the values calculated by the UltraSonic
  // hardware. In addition, the variable is initialized using the 
  // ping function from the NewPing class.
  float sensorData = sonarW.ping();

  // This bool variable will be used to return a true value if the
  // the object is detected and a false variable no objectt is detected.
  bool objDetected;

  // This variable is used to store the actual distance value. 
  float objDist;
  objDist = sensorData / US_ROUNDTRIP_MM;

  // This if statement uses a range in millimeters to determine if there
  // is an object in the next square. The range and the sensor needs to 
  // be tested and verified. 
  if(objDist >= 50 || objDist <= 305) {
    return true;
  }
  else {
    return false;
  }
}

// This function is used to determine if there is an obstacle on the field direction
// south of the robot. 
bool read_ObstacleS() {
  // This variable stores the values calculated by the UltraSonic
  // hardware. In addition, the variable is initialized using the 
  // ping function from the NewPing class.
  float sensorData = sonarS.ping();

  // This bool variable will be used to return a true value if the
  // the object is detected and a false variable no objectt is detected.
  bool objDetected;

  // This variable is used to store the actual distance value. 
  float objDist;
  objDist = sensorData / US_ROUNDTRIP_MM;

  // This if statement uses a range in millimeters to determine if there
  // is an object in the next square. The range and the sensor needs to 
  // be tested and verified. 
  if(objDist >= 50 || objDist <= 305) {
    return true;
  }
  else {
    return false;
  }
}

// This function is used to determine if there is an obstacle on the field direction
// east of the robot. 
bool read_ObstacleE() {
  // This variable stores the values calculated by the UltraSonic
  // hardware. In addition, the variable is initialized using the 
  // ping function from the NewPing class.
  float sensorData = sonarE.ping();

  // This bool variable will be used to return a true value if the
  // the object is detected and a false variable no objectt is detected.
  bool objDetected;

  // This variable is used to store the actual distance value. 
  float objDist;
  objDist = sensorData / US_ROUNDTRIP_MM;

  // This if statement uses a range in millimeters to determine if there
  // is an object in the next square. The range and the sensor needs to 
  // be tested and verified. 
  if(objDist >= 50 || objDist <= 305) {
    return true;
  }
  else {
    return false;
  }
}

/*
// This function will determine the configuration of the extension cord. There are 
// six different configurations. Each configuration will be identified by an integer
// variable (int values 1 - 6), look at the paper documentation for more information. 
// This function will return the int value of the configuration.
int cableConfig(float vN, float vE, float vS, float vW) {
  // The 'expectedV float variable will be determined during testing of the EMF 
  // sensors. This value is an expected voltage but the EMF sensors will rarely 
  // if ever return this value. The programmer must determine a percent range of 
  // acceptable voltage values.  
  const float expectedV = 5.0;

  const float minRangeV = 0.95 * expectV;
  const float maxRangeV = 1.05 * expectV;

  int configCableVal = 0;

  // The following six if statements determine the configuration of the extension cable 
  // at the current 1 square foot section. Config 1 is the cable running west to east. Config 2 
  // is the cable running north to south. Config 3 is the cable running north to east. Config 4
  // is the cable running south to east. Config 5 is the extension cable running west to south. 
  // Config 6 is the extension cable running west to north.
  if((minRangeV <= vW && vW <= maxRangeV) && (minRangeV <= vE && vE <= maxRangeV)) {
    configCableVal = 1; 
  }

  if((minRangeV <= vN && vN <= maxRangeV) && (minRangeV <= vS && vS <= maxRangeV)) {
    configCableVal = 2; 
  }

  if((minRangeV <= vN && vN <= maxRangeV) && (minRangeV <= vE && vE <= maxRangeV)) {
    configCableVal = 3; 
  }

    if((minRangeV <= vE && vE <= maxRangeV) && (minRangeV <= vS && vS <= maxRangeV)) {
    configCableVal = 4; 
  }

    if((minRangeV <= vW && vW <= maxRangeV) && (minRangeV <= vS && vS <= maxRangeV)) {
    configCableVal = 5; 
  }

    if((minRangeV <= vW && vW <= maxRangeV) && (minRangeV <= vN && vN <= maxRangeV)) {
    configCableVal = 6; 
  }

  return configCableVal;
*/

