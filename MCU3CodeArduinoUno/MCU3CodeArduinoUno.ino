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

// This integer variable is used for the position array. The
// position array will be used to determine the slowest and 
// fastest motor by analyzing the position.
const int MAX_MOTORS = 4;
int posArray[MAX_MOTORS] = {0, 0, 0, 0};

// This code section will be used for the history analysis of the
// motors. This portion is key for the integral component of the 
// PI control system.
const int MAX_HISTORY = 100;
int errHistM1[MAX_HISTORY];
int errHistM2[MAX_HISTORY];
int errHistM3[MAX_HISTORY];
int errHistM4[MAX_HISTORY];

// These integer variables will be used to store the smallest 
// and largest position values of the four motors. 
int smallestPos;
int largestPos;

// This float variable is used as a temp variable to determine if the
// half error value has a decimal value.
float tempError;

// The error value is determined by the largest position value minus
// the smallest position value. Then this error value is divided by 
// the value of two.
int halfOfError;

// This integer variable will be used as the guiding value for the 
// setSpeed of the motors. 
int targetValue; 

// These integer variables are used to store the ID of corresponding
// slowest and fastest motors. These two variables are currently not 
// being used but they could be used later in the finally program.
int motorSlowestID;
int motorFastestID;

// These variables are used as an argument for the setSpeed function of
// each corresponding motor.
int speedMotor1;
int speedMotor2;
int speedMotor3;
int speedMotor4;


//shit
// This integer variable will be determined during testing and 
// troubleshooting of the robot on the test course.
const float MAX_ERROR =100;
const float speedBound = 25.0;

// These variables will store the calculated gain PID values for 
// each motor. The integral component is the most important component
// for the calculation of each gain.  
float gainMotor1;
float gainMotor2;
float gainMotor3;
float gainMotor4;

// This 'toggleDecimal' bool variable will be used to correct the integer
// division error that occurs when the position average difference is calculated.
bool toggleDecimal;

// This float variable will be determined during testing and debugging of the
// robot on the test course.


// These two integer variables were included to prevent the PID control system
// from becoming unstable.
int upperBound;
int lowerBound;

void setup() 
{
 // Serial.begin(115200);
  
 

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

  // This code will initialize the history arrays to ensure that accurate
  // analysis results.
  for(int i = 0; i < MAX_HISTORY; i++) {
    errHistM1[i] = 0;
  }
  for(int i = 0; i < MAX_HISTORY; i++) {
    errHistM2[i] = 0;
  }
  for(int i = 0; i < MAX_HISTORY; i++) {
    errHistM3[i] = 0;
  }
  for(int i = 0; i < MAX_HISTORY; i++) {
    errHistM4[i] = 0;
  }

  smallestPos = 0;
  largestPos = 0;

  halfOfError = 0;
  
  // This code initializes the speed of the motors for
  // the first iteration. The value of the speed needs to
  // be determined in testing.
  speedMotor1 = 110;
  speedMotor2 = 110;
  speedMotor3 = 110;
  speedMotor4 = 110;

  targetValue = 0;

  gainMotor1 = 0.0;
  gainMotor2 = 0.0;
  gainMotor3 = 0.0;
  gainMotor4 = 0.0;

  toggleDecimal = false;

  upperBound = speedMotor1 + speedBound;
  lowerBound = speedMotor1 - speedBound -10;
}

// This void function acts just like the main function.
void loop() 
{

  
  motorSlowestID = 0;
  motorFastestID = 0;

  // These long variables are used to store the current position
  // value for each motor after the setSpeed function is executed.
  long newPosition1 = 0;
  long newPosition2 = 0;
  long newPosition3 = 0;
  long newPosition4 = 0;

    // These integer variables will store the sum of the corresponding
  // error values of the current iteration of every motor.
  float sumErrM1 = 0;
  float sumErrM2 = 0;
  float sumErrM3 = 0;
  float sumErrM4 = 0;

  // These functions send a position value to the encoders using
  // integers, within the write function software interrupts are 
  // called before and after the position initialization.
  encoder1.write(0);
  encoder2.write(0);
  encoder3.write(0);
  encoder4.write(0);

  //************* Direction North *******************************

  // This code determines the direction of the wheels.
  myMotor1->run(BACKWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(BACKWARD);

  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);


  

  // This code returns the absolute value of the position.
  newPosition1 = abs(encoder1.read());
  newPosition2 = abs(encoder2.read());
  newPosition3 = abs(encoder3.read());
  newPosition4 = abs(encoder4.read());
/*
 
  // The programmer determines to the distance traveled by
  // adjusting the speed.
  myMotor1->setSpeed(speedMotor1);
  myMotor2->setSpeed(speedMotor2);
  myMotor3->setSpeed(speedMotor3);
  myMotor4->setSpeed(speedMotor4);

  delay(2500);
*/

int innerloop=0;

while(((newPosition1+newPosition2+newPosition3+newPosition4)/4)<1400)

{

innerloop++;

  // This code returns the absolute value of the position.
  newPosition1 = abs(encoder1.read());
  newPosition2 = abs(encoder2.read());
  newPosition3 = abs(encoder3.read());
  newPosition4 = abs(encoder4.read());



/*/******************DEBUG*********************************
//fuckthis
Serial.println(" ");
Serial.println("Loop Number"); Serial.println(innerloop);
Serial.println(" ");
Serial.println(" ");
Serial.println("Motor Position");
Serial.println(newPosition1);
Serial.println(newPosition2);
Serial.println(newPosition3);
Serial.println(newPosition4);
Serial.println(" ");
Serial.println(" ");
Serial.println("Motor Speeds ");
Serial.println(speedMotor1);
Serial.println(speedMotor2);
Serial.println(speedMotor3);
Serial.println(speedMotor4);
Serial.println(" ");
Serial.println(" ");
Serial.println("Motor Gains ");
Serial.println(gainMotor1);
Serial.println(gainMotor2);
Serial.println(gainMotor3);
Serial.println(gainMotor4);
Serial.println("Motor Errors ");
Serial.println(errHistM1[0]);
Serial.println(errHistM2[0]);
Serial.println(errHistM3[0]);
Serial.println(errHistM4[0]);
Serial.println("error Sum ");
Serial.println(sumErrM1);
Serial.println(sumErrM2);
Serial.println(sumErrM3);
Serial.println(sumErrM4);


//**********************/




  posArray[0] = newPosition1;
  posArray[1] = newPosition2;
  posArray[2] = newPosition3;
  posArray[3] = newPosition4;

  // This section of code is used to determine the slowest and
  // fastest motor by analyzing the position values during the
  // current iteration.
  smallestPos = posArray[0];
  
  for(int i = 1; i < MAX_MOTORS; i++) {
    if(posArray[i] < smallestPos) {
      smallestPos = posArray[i];
      motorSlowestID = i;
    }
  }
  motorSlowestID++;
    
  largestPos = posArray[0];
  for(int j = 1; j < MAX_MOTORS; j++) {
    if(posArray[j] > largestPos) {
      largestPos = posArray[j];
      motorFastestID = j;
    }
  }
  motorFastestID++;

  // The main purpose of the 'tempError' variable is to correct the
  // integer decimal division error.
  tempError = (largestPos - smallestPos) / 2;

  halfOfError = (largestPos - smallestPos) / 2;
  targetValue = smallestPos + halfOfError;
 /* 
  *  
  Serial.println(" ");
  Serial.println(targetValue);
  Serial.println(" ");
*/
  // This if statement is used to detect and correct every other 0.5
  // value calculated when calculating the targetValue position calculation.
  if((tempError = tempError - (long)tempError) == 0.5) {
    toggleDecimal = !toggleDecimal;

    if(toggleDecimal) {
      targetValue++;
    }
  }
  

    
  // The following 4 for loops will be used to shift the current values
  // by one element to the right in the error history arrays for the 
  // corresponding motors. 
  for(int i = 0; i < MAX_HISTORY; i++) {
     errHistM1[i+1] = errHistM1[i]; 
  }
  for(int i = 0; i < MAX_HISTORY; i++) {
     errHistM2[i+1] = errHistM2[i]; 
  }
  for(int i = 0; i < MAX_HISTORY; i++) {
     errHistM3[i+1] = errHistM3[i]; 
  }    
  for(int i = 0; i < MAX_HISTORY; i++) {
     errHistM4[i+1] = errHistM4[i]; 
  }



  // This block of code inserts the current value of the error of each
  // motor into their corresponding error history array.
  errHistM1[0] = (targetValue - newPosition1);
  errHistM2[0] = (targetValue - newPosition2);
  errHistM3[0] = (targetValue - newPosition3);
  errHistM4[0] = (targetValue - newPosition4);

  // This block of code finds the sum of the error history for every
  // motor using for loops.
  for(int i = 0; i < MAX_HISTORY; i++) {
    sumErrM1 += errHistM1[i];
  }
  for(int i = 0; i < MAX_HISTORY; i++) {
    sumErrM2 += errHistM2[i];
  }
  for(int i = 0; i < MAX_HISTORY; i++) {
    sumErrM3 += errHistM3[i];
  }
  for(int i = 0; i < MAX_HISTORY; i++) {
    sumErrM4 += errHistM4[i];
  }

  // *******IMPORTANT***** These gain values have to determined during testing and debugging
  // on the test course. 0.0 - 1.0
  gainMotor1 = sumErrM1 / (MAX_ERROR * 100);
  gainMotor2 = sumErrM2 / (MAX_ERROR * 100);
  gainMotor3 = sumErrM3 / (MAX_ERROR * 100);
  gainMotor4 = sumErrM4 / (MAX_ERROR * 100);

  if(gainMotor1 == -0.00)
  {
    gainMotor1=0.00;
  }
 if(gainMotor2 == -0.00)
  {
    gainMotor2=0.00;
  }
   if(gainMotor3 == -0.00)
  {
    gainMotor3=0.00;
  }
   if(gainMotor4 == -0.00)
  {
    gainMotor4=0.00;
  }




  // This code sets the speed of all the motors to their new speed
  // that was calculated using the gain from the integral portion 
  // of the PID control system.


  
  speedMotor1 = speedMotor1 + (speedBound * gainMotor1);
  speedMotor2 = speedMotor2 + (speedBound * gainMotor2);
  speedMotor3 = speedMotor3 + (speedBound * gainMotor3);
  speedMotor4 = speedMotor4 + (speedBound * gainMotor4);

  // The following if statements will be used to ensure bounds
  // on the PID control system and prevent an unstable system.
  if(speedMotor1 > upperBound)
    speedMotor1 = upperBound;
  if(speedMotor2 > upperBound)
    speedMotor2 = upperBound;
  if(speedMotor3 > upperBound)
    speedMotor3 = upperBound;
  if(speedMotor4 > upperBound)
    speedMotor4 = upperBound;

  if(speedMotor1 < lowerBound)
    speedMotor1 = lowerBound;
  if(speedMotor2 < lowerBound)
    speedMotor2 = lowerBound;
  if(speedMotor3 < lowerBound)
    speedMotor3 = lowerBound;
  if(speedMotor4 < lowerBound)
    speedMotor4 = lowerBound;

  myMotor1->setSpeed(speedMotor1);
  myMotor2->setSpeed(speedMotor2);
  myMotor3->setSpeed(speedMotor3);
  myMotor4->setSpeed(speedMotor4);
  
  /* Debug code.
  // This code will change the value of the speedMotor argument
  // that will be used as an argument for the setSpeed function.
  // The inner ( ) is the proportional portion of the PI control
  // system.
  speedMotor1 = (speedMotor1 + (targetValue - newPosition1));
  speedMotor2 = (speedMotor2 + (targetValue - newPosition2));
  speedMotor3 = (speedMotor3 + (targetValue - newPosition3));
  speedMotor4 = (speedMotor4 + (targetValue - newPosition4));  
  */

  /* This is debug test code.
  Serial.println("Values after initialization!");
  Serial.println(newPosition1);
  Serial.println(newPosition2);
  Serial.println(newPosition3);
  Serial.println(newPosition4);
  Serial.println();
  
  Serial.println("Slowest motor and motor number.");
  Serial.println(smallestP);
  Serial.println(motorSlowestID);
  Serial.println("Fastest motor and motor number.");
  Serial.println(largestP);
  Serial.println(motorFastestID);
  Serial.println();
  */



  /*
  //************* Direction South *******************************

  delay(2500);

  myMotor1->run(FORWARD);
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  myMotor4->run(FORWARD);

  // This code returns the absolute value of the position.
  newPosition1 = abs(encoder1.read());
  newPosition2 = abs(encoder2.read());
  newPosition3 = abs(encoder3.read());
  newPosition4 = abs(encoder4.read());

  myMotor1->setSpeed(75);
  myMotor2->setSpeed(75);
  myMotor3->setSpeed(75);
  myMotor4->setSpeed(75);

  // Serial.println("Speed1 Now 75");
  // Serial.println("Speed2 Now 75");
  // Serial.println("Speed3 Now 75");
  // Serial.println("Speed4 Now 75");

  delay(2500);
 
  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);
  
  // myMotor1->run(RELEASE);
  // myMotor2->run(RELEASE);
  // myMotor3->run(RELEASE);
  // myMotor4->run(RELEASE);

  // This code returns the absolute value of the position.
  newPosition1 = abs(encoder1.read());
  newPosition2 = abs(encoder2.read());
  newPosition3 = abs(encoder3.read());
  newPosition4 = abs(encoder4.read());
     
  // Serial.println(newPosition1);
  // Serial.println(newPosition2);
  // Serial.println(newPosition3);
  // Serial.println(newPosition4);
  // Serial.println();
  */
}
  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);

delay(5000);

}

