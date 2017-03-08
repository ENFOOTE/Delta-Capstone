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
#include "ArrayLED.h"

#include <SPI.h>

const unsigned int MAX_EMF_SIZE = 300;

int EMF_valuesN[MAX_EMF_SIZE];
int EMF_valuesW[MAX_EMF_SIZE];
int EMF_valuesS[MAX_EMF_SIZE];
int EMF_valuesE[MAX_EMF_SIZE];

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

// These are four bool variables. Each bool value is determined by the 
// corresponding EMF sensor and it represents if there is a strong or 
// weak EMF signal near individual sensor.
bool signalNorthEMF;
bool signalWestEMF;
bool signalSouthEMF;
bool signalEastEMF;

int analogPinNorth = 0;
int analogPinWest = 1;
int analogPinSouth = 2;
int analogPinEast = 3;

// This function determines the configuration of the extension cable.
int cableConfig();

// This integer variable will be used to store a value that represents the
// current EMF cable configuration that is detected by the four EMF sensors. Int value
// 6 = config W-E, 7 = config N-S, 8 = config N-E, 9 = config S-E, 10 = config W-S,
// 11 = config N-W. The value will be used to communicate to the master via SPI.
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

// This void function is used to setup important features
// of the Arduino microprocessor board.
void setup() {
  Serial.begin(115200);

  pinMode(analogPinNorth, INPUT);
  pinMode(analogPinWest, INPUT);
  pinMode(analogPinSouth, INPUT);
  pinMode(analogPinEast, INPUT);

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
    // This is the constructor of the array implementation code from Jorge.
    ArrayLED mapObject;

    // This variable will be used to store whether or not there is an obstacle in
    // the upcoming one foot square section. It will be initialized with the return
    // value of one of the four bool read_Obstacle functions. 
    bool scan4Obstacle;

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
      EMF_SPI = cableConfig();

      // The if statement will only execute when any of the six EMF configurations
      // has been detected. The else statement will only execute when none of the 
      // six EMF configurations has been detected.
      if(EMF_SPI >= 7 && EMF_SPI <= 12) {
        // This code uses the current location of the robot (the current location is
        // determined by the mapping algorithm on the master MCU and sent by SPI 
        // command). 
      }
      else {
        
      }
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

// This function will determine the configuration of the extension cord. There are 
// six different configurations. Each configuration will be identified by an integer
// variable (int values 6 - 11), look at the paper documentation for more information. 
// This function will return the int value of the configuration and this configuration
// will be sent to the master MCU as a SPI command.
int cableConfig() {
  // This integer variable will be returned and it will represent the EMF 
  // cable configuration.
  int configCableVal = 0;
  
  // These four integer variables will be used to keep track of how many saturation 
  // samples for each corresponding EMF sensor.
  int countEMF_N = 0;
  int countEMF_W = 0;
  int countEMF_S = 0;
  int countEMF_E = 0;

  // These for bool variables will be used to store a true/false value that depends
  // on whether or not the EMF signal is strong for the corresponding EMF sensor.
  bool strongEMFsignalN;
  bool strongEMFsignalW;
  bool strongEMFsignalS;
  bool strongEMFsignalE;
  
  // This integer will be used by all four for loops that populate the EMF arrays for
  // corresponding sensors.
  unsigned int i;

  // These four for loops will populate the EMF arrays with binary numbers that represent
  // samples taken by EMF sensors and the onboard ADC of the Arduino.
  for(i = 0; i < MAX_EMF_SIZE; i++) {
    EMF_valuesN[i] = analogRead(analogPinNorth);
  }
  for(i = 0; i < MAX_EMF_SIZE; i++) {
    EMF_valuesW[i] = analogRead(analogPinWest);
  }
  for(i = 0; i < MAX_EMF_SIZE; i++) {
    EMF_valuesS[i] = analogRead(analogPinSouth);
  }
  for(i = 0; i < MAX_EMF_SIZE; i++) {
    EMF_valuesE[i] = analogRead(analogPinEast);
  }


  // These four for loops will record the number of times that the EMF sensor reaches
  // saturation.
  for(i = 0; i < MAX_EMF_SIZE; i++) {
    if(EMF_valuesN[i] == 1023) {
      countEMF_N++;
    }
  }
  for(i = 0; i < MAX_EMF_SIZE; i++) {
    if(EMF_valuesW[i] == 1023) {
      countEMF_W++;
    }
  }
  for(i = 0; i < MAX_EMF_SIZE; i++) {
    if(EMF_valuesS[i] == 1023) {
      countEMF_S++;
    }
  }
  for(i = 0; i < MAX_EMF_SIZE; i++) {
    if(EMF_valuesE[i] == 1023) {
      countEMF_E++;
    }
  }

  // These if/else statements will determine if the EMF sensor detects a 
  // strong EMF signal or a weak signal for the corresponding EMF sensor. 
  if(countEMF_N >= /*some number*/){
    strongEMFsignalN = true;
  }
  else {
    strongEMFsignalN = false;
  }
  if(countEMF_W >= /*some number*/){
     strongEMFsignalW = true;
  }
  else {
    strongEMFsignalW = false;
  }
  if(countEMF_S >= /*some number*/){
     strongEMFsignalS = true;
  }
  else {
    strongEMFsignalS = false;
  }
  if(countEMF_E >= /*some number*/){
     strongEMFsignalE = true;
  }
  else {
    strongEMFsignalE = false;
  }

  // These if statements will determine the EMF cable configuration.
  if(strongEMFsignalW == true && strongEMFsignalE == true) {
    configCableVal = 7;
  }
  if(strongEMFsignalN == true && strongEMFsignalS == true) {
    configCableVal = 8;
  }
  if(strongEMFsignalN == true && strongEMFsignalE == true) {
    configCableVal = 9;
  }
  if(strongEMFsignalS == true && strongEMFsignalE == true) {
    configCableVal = 10;
  }
  if(strongEMFsignalW == true && strongEMFsignalS == true) {
    configCableVal = 11;
  }
  if(strongEMFsignalN == true && strongEMFsignalW == true) {
    configCableVal = 12;
  }
  if(strongEMFsignalN == false && strongEMFsignalW == false && strongEMFsignalS == false && strongEMFsignalE == false) {
    configCableVal = 13;
  }
  
  return configCableVal;
}


