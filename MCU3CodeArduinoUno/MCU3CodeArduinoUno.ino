// EE4390 EE Design I
// Date created: December 01, 2016 
// Author One: David S Vasquez
// Author Two: Eric Foote
// Author Three: Jorge Villalobos

// Information: This is the master code program for MCU3 Arduino Uno
// board. This program will be used by all the hardware connected to 
// this board. It will communicate with the Arduino Mega board using
// SPI. 

// This void function is used to setup important features
// of the Arduino microprocessor board.


/* 
This is a movement test for the R5 Team Delta Robot. It currently executes a pattern:
Move North, Move East, Move South, Move West.  Encoders have not been implemented yet,
And so the movement is not precise or measurably accurate.

To use this program, it is necessary to first import the Libray located here:
https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/install-software

The zip file must be extracted to the C:\Users\Llama Shaman\Documents\Arduino\libraries Folder.

*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Encoder.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'ports' M1, M2, M3 or M4.
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

Encoder encoder1(18, 22);

void setup() 
{
  Serial.begin(115200);
  
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  Serial.println("Basic Encoder Test:");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  
  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);
  
  myMotor1->run(BACKWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(BACKWARD);
  
  // turn on motor
  
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);

}

long oldPosition  = -999;

// This void function acts just like the main function.
void loop() 
{
  uint8_t i;
  uint8_t MAX_SPEED = 30;
  uint8_t DELAY = 10;

 long newPosition = encoder1.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }


 
  
 //************* NORTH ********************

  myMotor1->run(BACKWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(BACKWARD);

  for (i=0; i<MAX_SPEED; i++) 
  {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);
    myMotor3->setSpeed(i);  
    myMotor4->setSpeed(i);

    delay(DELAY);
    
  }
    delay(1000);
  for (i=MAX_SPEED; i!=0; i--) 
  {
    myMotor1->setSpeed(i); 
    myMotor2->setSpeed(i); 
    myMotor3->setSpeed(i); 
    myMotor4->setSpeed(i); 

    
    delay(DELAY);

  }
    newPosition = encoder1.read();
    Serial.println("After moving North");
    Serial.println(newPosition);
    
  //************* EAST ********************
 
  myMotor1->run(BACKWARD);
  myMotor2->run(BACKWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(FORWARD);  
  
  for (i=0; i<MAX_SPEED; i++) 
  {
    
    myMotor2->setSpeed(i);  
    myMotor3->setSpeed(i);
    myMotor4->setSpeed(i);  
    myMotor1->setSpeed(i);
       
    delay(DELAY);
    
  }

  delay(1000);
  
  for (i=MAX_SPEED; i!=0; i--) 
  {
    
    myMotor2->setSpeed(i);  
    myMotor3->setSpeed(i); 
    myMotor4->setSpeed(i);  
    myMotor1->setSpeed(i); 
   
    delay(DELAY);
    
  }

    newPosition = encoder1.read();
    Serial.println("After moving East");
    Serial.println(newPosition);
    
  //************* SOUTH ********************
 
  myMotor1->run(FORWARD);
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  myMotor4->run(FORWARD);  
  
  for (i=0; i<MAX_SPEED; i++) 
  {    
    myMotor3->setSpeed(i);
    myMotor4->setSpeed(i); 
    myMotor1->setSpeed(i);
    myMotor2->setSpeed(i); 
       
    delay(DELAY);
  }

   delay(1000);
  
  for (i=MAX_SPEED; i!=0; i--) 
  {
    myMotor3->setSpeed(i); 
    myMotor4->setSpeed(i);
    myMotor1->setSpeed(i); 
    myMotor2->setSpeed(i);   
    
    delay(DELAY);
    
  }
    newPosition = encoder1.read();
    Serial.println("After moving South");
    Serial.println(newPosition);
    
  //************* WEST ********************
 
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(BACKWARD);
  myMotor4->run(BACKWARD);  
  
  for (i=0; i<MAX_SPEED; i++) 
  {
    myMotor4->setSpeed(i);
    myMotor1->setSpeed(i);
    myMotor2->setSpeed(i);  
    myMotor3->setSpeed(i);    
       
    delay(DELAY);
    
  }

delay(1000);
  
  for (i=MAX_SPEED; i!=0; i--) 
  {
    myMotor4->setSpeed(i);
    myMotor1->setSpeed(i); 
    myMotor2->setSpeed(i);  
    myMotor3->setSpeed(i); 
      
    delay(DELAY);
    
  }
    newPosition = encoder1.read();
    Serial.println("After moving West");
    Serial.println(newPosition);

  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);
  delay(1000);

}

