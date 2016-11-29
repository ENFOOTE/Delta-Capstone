// EE4390 EE Design I
// Date created: November 26, 2016 
// Author One: David S Vasquez
// Author Two: Eric Foote
// Author Three: Jorge Villalobos

// Information: This is the master code program. This program
// will be used by all the hardware. This program will run the
// entire robot from the beginning of execution until the end. 

// This library is for the UltraSonic Distance Sensor
#include <NewPing.h>

// These defined constant variables are for the implementation 
// of the UltraSonic distance sensor. The variable called 
// 'US_ROUNDTRIP_MM' was created specifically so the sensor would 
// return distance values in millimeters. Normally, the sensor
// would return values in centimeters.
#define TRIGGER_PIN 8
#define ECHO_PIN 7
#define MAX_DISTANCE 200
#define US_ROUNDTRIP_MM 5.7

// This constructor is for the UltraSonic Distance Sensor.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX)

// This void function is used to setup important features
// of the Arduino microprocessor board.
void setup() {
  Serial.begin(115200);

}

// This void function acts just like the main function.
void loop() {

  // This code is to enable the UltraSonic Sensor. For now
  // the code will be commented out.
  // double uS = sonar.ping();


}
