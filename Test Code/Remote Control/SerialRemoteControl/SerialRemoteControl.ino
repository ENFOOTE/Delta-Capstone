 // EE4390 EE Design I and EE4391 EE Design II
// Date created: January 03, 2017
// Programmer one: Eric Foote
// Programmer two: David S Vasquez
// Programmer three: Jorge Villalobos
// Programmer four:
// Information: This is the motor calibration code using PID to adjust the 
// robot in response to the slowest motor(s). 

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

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// This code creates the motor shield object with a different I2C address 
// (say for stacking).
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'ports' M1, M2, M3 or M4.
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

//shit


// These variables will store the calculated gain PID values for 
// each motor. The integral component is the most important component
// for the calculation of each gain.  
float gainMotor1;
float gainMotor2;
float gainMotor3;
float gainMotor4;


void setup() 
{

#if DEBUG  
  Serial.begin(115200);
#endif  
 

  // This initializes the Adafruit Motorshield with a default
  // frequency 1.6 KHz. 
  AFMS.begin();
  
  // It is possible to initialize the Adafruit Motorshield with 
  // a specific frequency and in this case it is 1 KHz.
  // AFMS.begin(1000);
  
  // This code sets the speed to start the motors, in this case speed zero.
  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);

 /*
  // This code initializes the speed of the motors for
  // the first iteration. The value of the speed needs to
  // be determined in testing.
  speedMotor1 = 100;
  speedMotor2 = 114;
  speedMotor3 = 116;
  speedMotor4 = 100;
}
*/

  speedMotor1 = 60;
  speedMotor2 = 60;
  speedMotor3 = 60;
  speedMotor4 = 60;
}

// This void function acts just like the main function.
void loop() 
{

  

  encoder1.write(0);
  encoder2.write(0);
  encoder3.write(0);
  encoder4.write(0);

  newPosition1 = abs(encoder1.read());
  newPosition2 = abs(encoder2.read());
  newPosition3 = abs(encoder3.read());
  newPosition4 = abs(encoder4.read());


  Serial.println("Please Enter A Direction:");
  
  
  while (Serial.available()==0)  //Wait for user input.
  {            
  }
  
  Bearing=Serial.read();  //Read user input.
  Serial.println(Bearing);
  delay(100);
if(Bearing == '8' || Bearing == '2' || Bearing == '4' || Bearing == '6' || Bearing == '5' || Bearing == '7' || Bearing == '9')
{
  set_Direction(Bearing);
}


#if DEBUG
  //Serial.println("Motor Position");
  Serial.println(newPosition1);
  Serial.println(newPosition2);
  Serial.println(newPosition3);
  Serial.println(newPosition4);
  Serial.println(" ");
#endif

}

void set_Direction(char Direction)
{
/*  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);
  */
  delay(500);

  
 
  if (Direction == '8')
  {
    myMotor1->run(BACKWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(BACKWARD);
  }

  if (Direction == '2') 
  {
    myMotor1->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);
  }

    if (Direction == '4') 
  {
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(BACKWARD);
  }

      if (Direction == '6') 
  {
    myMotor1->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(FORWARD);
  }

        if (Direction == '7') 
  {
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(FORWARD);
  }

        if (Direction == '9') 
  {
    myMotor1->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(BACKWARD);
  }

if (Direction  == '8' || Direction == '2' || Direction == '4' || Direction == '6')
{
  myMotor1->setSpeed(speedMotor1);
  myMotor2->setSpeed(speedMotor2);
  myMotor3->setSpeed(speedMotor3);
  myMotor4->setSpeed(speedMotor4);
}

if (Direction == '7' || Direction == '9')
{
  myMotor1->setSpeed(30);
  myMotor2->setSpeed(30);
  myMotor3->setSpeed(30);
  myMotor4->setSpeed(30);
}

if (Direction == '5')
{
  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);

  }

  
}


