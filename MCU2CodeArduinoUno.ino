// EE4390 EE Design I
// Date created: December 01, 2016 
// Author One: David S Vasquez
// Author Two: Eric Foote
// Author Three: Jorge Villalobos

// Information: This is the master code program for the Arduino Uno
// board. This program will be used by all the hardware connected to 
// this board. This program communicate with the Mega board. 

// This library is for the UltraSonic Distance Sensor
#include <NewPing.h>

// The variable called 'US_ROUNDTRIP_MM' was created specifically so 
// the sensor would return distance values in millimeters. Normally, 
// the sensor would return values in centimeters.
#define US_ROUNDTRIP_MM 5.7

// This constructor is for the UltraSonic Distance Sensor.
NewPing sonar(TRIGGER_PIN = 8, ECHO_PIN = 7, MAX_DISTANCE = 200);

// This function will return a True or False bool value depending on
// if an obstacle is detected on the field.
bool read_Obstacle();

// This void function is used to setup important features
// of the Arduino microprocessor board.
void setup() {
  Serial.begin(115200);

}

// This void function acts just like the main function.
void loop() {
  // This code is to enable the UltraSonic Sensor. For now
  // the code will be commented out.
  double uS = sonar.ping();


}

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

