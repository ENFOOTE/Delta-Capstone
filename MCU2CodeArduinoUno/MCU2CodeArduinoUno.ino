// EE4390 EE Design I
// Date created: December 01, 2016 
// Author One: David S Vasquez
// Author Two: Eric Foote
// Author Three: Jorge Villalobos
// Libraries: "NewPing.h" is used for the UltraSonic Distance Sensor, "SPI.h" 
// is used for the SPI communication between the Arduino boards.
// Information: This is the master code program for the Arduino Uno
// board (second board MC2). This program will be used by all the 
// hardware connected to this board. This program communicate with 
// the Mega board. 

#include "NewPing.h"
#include "EMFSensor.h"
#include "CapacitiveSensor.h"
#include <SPI.h>

// This declaration and initialization is for the Slave Select Pin. The
// SPI library will automatically set the other SPI Pins.
int SS = 10;

// The variable called 'US_ROUNDTRIP_MM' was created specifically so 
// the sensor would return distance values in millimeters. Normally, 
// the sensor would return values in centimeters.
#define US_ROUNDTRIP_MM 5.7

// This constructor is for the UltraSonic Distance Sensor.
NewPing sonar(TRIGGER_PIN = 8, ECHO_PIN = 7, MAX_DISTANCE = 200);

// This function will return a True or False bool value depending on
// if an obstacle is detected on the field.
bool read_Obstacle();

// This function determines the configuration of the extension cable.
int cableConfig(float, float, float, float);

// These four constructors are for the four EMF Sensors. I labeled them 
// as N=North, S=South, W=West, E=East.
EMFSensor sensorN;
EMFSensor sensorS;
EMFSensor sensorW;
EMFSensor sensorE;

// This is the constructor for the capacitive sensor.
CapacitiveSensor sensorC;

// This void function is used to setup important features
// of the Arduino microprocessor board.
void setup() {
  
  Serial.begin(115200);

  /*
  // This code is related to the SPI communication code.
  // This sets SS pin directions.
  pinMode(SS, OUTPUT);

  // Initialize SPI
  SPI.begin();

  SPI.setBitOrder(MSBFIRST);
  */
}

// This void function acts just like the main function.
void loop() {
  // This variable will be used to store whether or not there is an obstacle in
  // the upcoming one foot square section.
  bool scan4Obstacle;

  // These four bool variables will be used by the corresponding
  // EMF sensor.
  bool voltDectN;
  bool voltDectE;
  bool voltDectS;
  bool voltDectW;

  // This variable will be used to store whether or not there is insulation 
  // below the layer of glass.
  bool insulationDect;

  // This variable will be used to communicate to the MCU that drives the motors.
  int currentCableConfig = 0;
  
  // Use the read_Obstacle function to determine if there is an
  // obstacle.
  scan4Obstacle = read_Obstacle;

  if(scan4Obstacle == false) {
    voltDectN = false;
    voltDectE = false;
    voltDectS = false;
    voltDectW = false;
    
    // This code uses all four EMF sensors to scan for a voltage.
    sensorN.getVoltage();
    sensorE.getVoltage();
    sensorS.getVoltage();
    sensorW.getVoltage();

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
      
      
    }
    else {
      //  This code will determine whether or not there is insulation present at the current
      // location of the robot. 
      

      // This if statement will determine whether or not there is insulation present below 
      // the glass layer.
      if( ) {
        
      }
    }
  }
  else
  {
    // This else statement will send a variable to the MCU that drives the motors. The purpose of 
    // variable is to adjust the path of the robot to avoid the obstacle.
  }
}

// This function is used to determine if there is an obstacle on the i
bool read_Obstacle() {
  // This variable stores the values calculated by the UltraSonic
  // hardware. In addition, the variable is initialized using the 
  // ping function from the NewPing class.
  float sensorData = sonar.ping();

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
// variable (int values 1 - 6), look at the paper documentation for more information. This 
// function will return the int value of the configuration.
int cableConfig(float vN, float vE, float vS, float vW) {
  // The 'expectedV float variable will be determined during testing of the EMF sensors. This
  // value is an expected voltage but the EMF sensors will rarely if ever return this value. The
  // programmer must determine a percent range of acceptable voltage values.  
  const float expectedV = 5.0;

  const float minRangeV = 0.95 * expectV;
  const float maxRangeV = 1.05 * expectV;

  int configCable = 0;

  // The following six if statements determine the configuration of the extension cable 
  // at the current 1 square foot section. Config 1 is the cable running west to east. Config 2 
  // is the cable running north to south. Config 3 is the cable running north to east. Config 4
  // is the cable running south to east. Config 5 is the extension cable running west to south. 
  // Config 6 is the extension cable running west to north.
  if((minRangeV <= vW && vW <= maxRangeV) && (minRangeV <= vE && vE <= maxRangeV)) {
    configCable = 1; 
  }

  if((minRangeV <= vN && vN <= maxRangeV) && (minRangeV <= vS && vS <= maxRangeV)) {
    configCable = 2; 
  }

  if((minRangeV <= vN && vN <= maxRangeV) && (minRangeV <= vE && vE <= maxRangeV)) {
    configCable = 3; 
  }

    if((minRangeV <= vE && vE <= maxRangeV) && (minRangeV <= vS && vS <= maxRangeV)) {
    configCable = 4; 
  }

    if((minRangeV <= vW && vW <= maxRangeV) && (minRangeV <= vS && vS <= maxRangeV)) {
    configCable = 5; 
  }

    if((minRangeV <= vW && vW <= maxRangeV) && (minRangeV <= vN && vN <= maxRangeV)) {
    configCable = 6; 
  }

  return configCable;
}

