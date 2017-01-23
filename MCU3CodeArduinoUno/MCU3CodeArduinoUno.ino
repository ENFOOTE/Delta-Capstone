// EE4390 EE Design I
// Date created: December 01, 2016
// Programmer One: David S Vasquez
// Programmer Two: Eric Foote
// Programmer Three: Jorge Villalobos

// Information: This program is being used to test the power button code, SPI,
// the motor encoder code all together.

#include <SPI.h>
#include "SPI_Template.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Encoder.h>

typedef struct myStruct
{
  int a;
  float b;
  long c;
};

myStruct structComm1;
myStruct structComm2;
bool haveData = false;
bool haveData1 = false;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'ports' M1, M2, M3 or M4.
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

Encoder encoder1(2, 22);
Encoder encoder2(3, 23);
Encoder encoder3(18, 24);
Encoder encoder4(19, 25);

void setup()
{
  Serial.begin(115200);

  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  Serial.println("Basic Encoder Test:");

  pinMode(MISO, OUTPUT);

  // This code turns on the SPI in slave mode.
  SPCR |= _BV(SPE);

  SPI.attachInterrupt();

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

  // This code turns on the motors.
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);

}

long oldPosition  = -999;

// This void function acts just like the main function.
void loop() {
  uint8_t i;
  uint8_t MAX_SPEED = 75;
  uint8_t DELAY = 10;

  long newPosition1 = 0;
  long newPosition2 = 0;
  long newPosition3 = 0;
  long newPosition4 = 0;

  if (haveData) {
    delay(2500);

    encoder1.write(0);
    encoder2.write(0);
    encoder3.write(0);
    encoder4.write(0);

    //************* NORTH ********************

    myMotor1->run(BACKWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(BACKWARD);

    for (i = 0; i < MAX_SPEED; i++) {
      myMotor1->setSpeed(i);
      newPosition1 = abs(encoder1.read());
      Serial.println("Encoder 1:" );
      Serial.println(newPosition1);

      myMotor2->setSpeed(i);
      newPosition2 = abs(encoder2.read());
      Serial.println("Encoder 2:" );
      Serial.println(newPosition2);

      myMotor3->setSpeed(i);
      newPosition3 = abs(encoder3.read());
      Serial.println("Encoder 3:" );
      Serial.println(newPosition3);

      myMotor4->setSpeed(i);
      newPosition4 = abs(encoder4.read());
      Serial.println("Encoder 4:" );
      Serial.println(newPosition4);

      delay(DELAY);
    }

    newPosition1 = abs(encoder1.read());
    newPosition2 = abs(encoder2.read());
    newPosition3 = abs(encoder3.read());
    newPosition4 = abs(encoder4.read());

    while ( ((newPosition1 + newPosition2 + newPosition3 + newPosition4) / 4) < 3500) {
      newPosition1 = abs(encoder1.read());
      newPosition2 = abs(encoder2.read());
      newPosition3 = abs(encoder3.read());
      newPosition4 = abs(encoder4.read());
    }

    myMotor1->setSpeed(50);
    Serial.println("Speed1 Now 50");
    Serial.println(newPosition1);

    myMotor2->setSpeed(50);
    Serial.println("Speed2 Now 50");
    Serial.println(newPosition2);

    myMotor3->setSpeed(50);
    Serial.println("Speed3 Now 50");
    Serial.println(newPosition3);

    myMotor4->setSpeed(50);
    Serial.println("Speed4 Now 50");
    Serial.println(newPosition4);

    while (((newPosition1 + newPosition2 + newPosition3 + newPosition4) / 4) < 4500) {
      newPosition1 = abs(encoder1.read());
      newPosition2 = abs(encoder2.read());
      newPosition3 = abs(encoder3.read());
      newPosition4 = abs(encoder4.read());
    }

    myMotor1->setSpeed(25);
    Serial.println("Speed Now 25");
    Serial.println(newPosition1);

    myMotor2->setSpeed(25);
    Serial.println("Speed2 Now 25");
    Serial.println(newPosition2);

    myMotor3->setSpeed(25);
    Serial.println("Speed3 Now 25");
    Serial.println(newPosition3);

    myMotor4->setSpeed(25);
    Serial.println("Speed4 Now 25");
    Serial.println(newPosition4);

    while (((newPosition1 + newPosition2 + newPosition3 + newPosition4) / 4) < 5000) {
      newPosition1 = abs(encoder1.read());
      newPosition2 = abs(encoder2.read());
      newPosition3 = abs(encoder3.read());
      newPosition4 = abs(encoder4.read());
    }

    myMotor1->run(RELEASE);
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);

    //************SOUTH************************

    delay(2500);

    encoder1.write(0);
    encoder2.write(0);
    encoder3.write(0);
    encoder4.write(0);

    myMotor1->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);

    for (i = 0; i < MAX_SPEED; i++) {
      myMotor3->setSpeed(i);
      newPosition3 = abs(encoder3.read());
      Serial.println("Encoder 3:" );
      Serial.println(newPosition3);

      myMotor4->setSpeed(i);
      newPosition4 = abs(encoder4.read());
      Serial.println("Encoder 4:" );
      Serial.println(newPosition4);

      myMotor1->setSpeed(i);
      newPosition1 = abs(encoder1.read());
      Serial.println("Encoder 1:" );
      Serial.println(newPosition1);

      myMotor2->setSpeed(i);
      newPosition2 = abs(encoder2.read());
      Serial.println("Encoder 2:" );
      Serial.println(newPosition2);

      delay(DELAY);
    }

    newPosition1 = abs(encoder1.read());
    newPosition2 = abs(encoder2.read());
    newPosition3 = abs(encoder3.read());
    newPosition4 = abs(encoder4.read());

    while ( ((newPosition1 + newPosition2 + newPosition3 + newPosition4) / 4) < 3500) {
      newPosition1 = abs(encoder1.read());
      newPosition2 = abs(encoder2.read());
      newPosition3 = abs(encoder3.read());
      newPosition4 = abs(encoder4.read());
    }

    myMotor3->setSpeed(50);
    Serial.println("Speed3 Now 50");
    Serial.println(newPosition3);

    myMotor4->setSpeed(50);
    Serial.println("Speed4 Now 50");
    Serial.println(newPosition4);

    myMotor1->setSpeed(50);
    Serial.println("Speed1 Now 50");
    Serial.println(newPosition1);

    myMotor2->setSpeed(50);
    Serial.println("Speed2 Now 50");
    Serial.println(newPosition2);

    while (((newPosition1 + newPosition2 + newPosition3 + newPosition4) / 4) < 4500) {
      newPosition1 = abs(encoder1.read());
      newPosition2 = abs(encoder2.read());
      newPosition3 = abs(encoder3.read());
      newPosition4 = abs(encoder4.read());
    }

    myMotor3->setSpeed(25);
    Serial.println("Speed3 Now 25");
    Serial.println(newPosition3);

    myMotor4->setSpeed(25);
    Serial.println("Speed4 Now 25");
    Serial.println(newPosition4);

    myMotor1->setSpeed(25);
    Serial.println("Speed Now 25");
    Serial.println(newPosition1);

    myMotor2->setSpeed(25);
    Serial.println("Speed2 Now 25");
    Serial.println(newPosition2);

    while (((newPosition1 + newPosition2 + newPosition3 + newPosition4) / 4) < 5000) {
      newPosition1 = abs(encoder1.read());
      newPosition2 = abs(encoder2.read());
      newPosition3 = abs(encoder3.read());
      newPosition4 = abs(encoder4.read());
    }

    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);
    myMotor1->run(RELEASE);
    myMotor2->run(RELEASE);

    //************* EAST ********************
    //************* SOUTH *******************
    //************* WEST ********************
  }

  // This if statement executes when the red button has been pressed. The while loop is
  // an infinite loop that is suppose to freeze the void loop function.
  if (haveData1) {
    while (1) { }
  }
}

// This is a SPI interrupt routine function for the green go button and the red stop
// button.
ISR(SPI_STC_vect) {
  SPI_readAnything_ISR(structComm1);
  SPI_readAnything_ISR(structComm2);
  haveData = true;
  haveData1 = true;
}
