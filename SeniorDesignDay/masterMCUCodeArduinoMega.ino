// EE4391 EE Design II
// Date created: March 24, 2017
// Programmer One: Eric Foote
// Programmer Two: Geovanni Hernandez
// Programmer Three: Jorge Villalobos
// Programmer Four: David S Vasquez
// Information: This program will be used to demostrate the several working 
// functions and abilities of the robot. Currently, the wheels, robot arm, 
// ultrasonic sensors, and EMF sensors are working.

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Encoder.h>

#define DEBUG         1
#define POSITION      0
#define MOTORSPEEDS   0
#define MOTORGAINS    0
#define MOTORERRORS   0
#define ERRORSUM      0

void set_Direction(char);

// This creates the motor shield object with the default I2C address.
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// This code creates the motor shield object with a different I2C address 
// (say for stacking).
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// This code selects which 'ports' will be M1, M2, M3 or M4.
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

// These are the declarations of the pins that are used for the encoders,
// the first pin is the hard interrupt and the second pin is used for the
// software interrupt.
Encoder encoder1(2, 22);
Encoder encoder2(3, 23);
Encoder encoder3(18, 24);
Encoder encoder4(19, 25);

char Bearing;

int speedMotor1;
int speedMotor2;
int speedMotor3;
int speedMotor4;

long newPosition1 = 0;
long newPosition2 = 0;
long newPosition3 = 0;
long newPosition4 = 0;

// These variables will store the calculated gain PID values for 
// each motor. The integral component is the most important component
// for the calculation of each gain.  
float gainMotor1;
float gainMotor2;
float gainMotor3;
float gainMotor4;

void setup() {
  Serial.begin(115200);

  Serial.println("Robot demonstration.");

  // This initializes the Adafruit Motorshield with a default frequency
  // of 1.6 KHz.
  AFMS.begin();

  // This code sets the initial speed of the motors, in this case speed zero.
  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);
}

// This loop function will contain the code for operating the wheels and
// the robotic arm. If time allows it, this code will execute the EMF and
// ultrasonic sensors.
void loop() {
  // This string variable will be used for keyboard input. Input 'r' executes the
  // robotic arm functionality. Input 'w' executes the wheels functionality. Input
  // 'e' executes the EMF sensors. Input 'u' executes the ultrasonic sensors.
  String inputArg;

  Serial.println("Enter 'w' for wheels or 'r' for robotic arm.");
  while(Serial.available() == 0) {
  }
  inputArg = Serial.readString();

  delay(2500);

  // This while loop will be used to execute the wheel functionality. 
  while(inputArg == "w" || inputArg == "W") {
    // This argument will be used to exit this while loop.
    String exitArg;
    
    Serial.println("Wheel functionality enabled.");
    
    delay(1000);

    encoder1.write(0);
    encoder2.write(0);
    encoder3.write(0);
    encoder4.write(0);

    newPosition1 = abs(encoder1.read());
    newPosition2 = abs(encoder2.read());
    newPosition3 = abs(encoder3.read());
    newPosition4 = abs(encoder4.read());

    Serial.println("Please Enter A Direction:");
  
    // This while loop waits for serial user input.
    while(Serial.available()==0){            
    }
  
    Bearing = Serial.read();
    Serial.println(Bearing);
    delay(100);
    
    if(Bearing == '8' || Bearing == '2' || Bearing == '4' || Bearing == '6' || Bearing == '5' || Bearing == '7' || Bearing == '9') {
      set_Direction(Bearing);
    }    

    exitArg = Serial.readString();
    if(exitArg == "q") {
      Serial.println("Wheel funtionality has ended.");
      break;
    }
  }
  
  // This while loop will be used to execute the robotic arm functionality.
  while(inputArg == "r" || inputArg == "R") {
    // This argument will be used to exit this while loop.
    String exitArg;

    Serial.println("Robotic arm functionality enabled.");

    delay(2500);

    exitArg = Serial.readString();
    if(exitArg == "q") {
      Serial.println("Robotic arm functionality has ended.");
      break;
    }
  }
}

void set_Direction(char moveDirection) {
  delay(500);

  if(moveDirection == '8') {
    myMotor1->run(BACKWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(BACKWARD);
  }
  if(moveDirection == '2') {
    myMotor1->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);
  }
  if(moveDirection == '4') {
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(BACKWARD);
  }
  if(moveDirection == '6') {
    myMotor1->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(FORWARD);
  }
  if(moveDirection == '7') {
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(FORWARD);
  }
  if(moveDirection == '9') {
    myMotor1->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(BACKWARD);
  }
  if(moveDirection  == '8' || moveDirection == '2' || moveDirection == '4' || moveDirection == '6') {
    myMotor1->setSpeed(speedMotor1);
    myMotor2->setSpeed(speedMotor2);
    myMotor3->setSpeed(speedMotor3);
    myMotor4->setSpeed(speedMotor4);
  }
  if(moveDirection == '7' || moveDirection == '9') {
    myMotor1->setSpeed(30);
    myMotor2->setSpeed(30);
    myMotor3->setSpeed(30);
    myMotor4->setSpeed(30);
  }
  if(moveDirection == '5') {
    myMotor1->setSpeed(0);
    myMotor2->setSpeed(0);
    myMotor3->setSpeed(0);
    myMotor4->setSpeed(0);
  }
}


