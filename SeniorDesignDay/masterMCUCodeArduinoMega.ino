// EE4391 EE Design II
// Date created: April 19, 2017
// Programmer One: Eric Foote
// Programmer Two: Geovanni Hernandez
// Programmer Three: Jorge Villalobos
// Programmer Four: David S Vasquez
// Information: This program will be used to demostrate the several working 
// functions and abilities of the robot. Currently, the wheels, robot arm, 
// ultrasonic sensors, and EMF sensors are working.

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Encoder.h>

#define DEBUG         1
#define POSITION      0
#define MOTORSPEEDS   0
#define MOTORGAINS    0
#define MOTORERRORS   0
#define ERRORSUM      0

void set_Direction(char);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

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

char Bearing;

int speedMotor1;
int speedMotor2;
int speedMotor3;
int speedMotor4;

void setup() {
  #if DEBUG
    Serial.begin(115200);
  #endif

  Serial.println("Robot demonstration.");

  // This initializes the Adafruit Motorshield with a default frequency
  // of 1.6 KHz.
  AFMS.begin();

  // This code sets the initial speed of the motors, in this case speed zero.
  myMotor1->setSpeed(0);
  myMotor2->setSpeed(0);
  myMotor3->setSpeed(0);
  myMotor4->setSpeed(0);

  //pwm.begin();
  //pwm.setPWMFreq(60);

  // Serial.flush();

  speedMotor1 = 60;
  speedMotor2 = 60;
  speedMotor3 = 60;
  speedMotor4 = 60;
}

// This loop function will contain the code for operating the wheels and
// the robotic arm. If time allows it, this code will execute the EMF and
// ultrasonic sensors.
void loop() {
  pwm.begin();
  pwm.setPWMFreq(50);  // workingfreq MG995 50Hz
      
  String argument0;
  String argument1;
  String argument2;
  String Part;

  String exitArmMode;
  
  int tick;
  
  // This string variable will be used for keyboard input. Input 'r' executes the
  // robotic arm functionality. Input 'w' executes the wheels functionality. Input
  // 'e' executes the EMF sensors. Input 'u' executes the ultrasonic sensors.
  String inputArg;

  Serial.println("Enter 'w' for wheels or 'r' for robotic arm.");
  while(Serial.available() == 0) {
  }
  inputArg = Serial.readString();

  if(inputArg == "w" || inputArg == "W") {
    Serial.println("Wheel functionality enabled.");
    Serial.println();
  }

  // This while loop will be used to execute the wheel functionality. 
  while(inputArg == "w" || inputArg == "W") {

    Serial.println("Please Enter A Direction:");
  
    // This while loop waits for serial user input.
    while(Serial.available()==0){            
    }
  
    Bearing = Serial.read();
    Serial.println(Bearing);
    delay(100);
    
    if(Bearing == '8' || Bearing == '2' || Bearing == '4' || Bearing == '6' ||
       Bearing == '5' || Bearing == '7' || Bearing == '9') {
      set_Direction(Bearing);
    }    

    if(Bearing == 'q') {
      Serial.println("Wheel funtionality has ended.");
      set_Direction('5');
      break;
    }
  }

  if(inputArg == "r" || inputArg == "R") {
    Serial.println("Robotic arm functionality enabled.");
    Serial.println();
  }
  
  // This while loop will be used to execute the robotic arm functionality.
  while(inputArg == "r" || inputArg == "R") {
    Serial.println("Please select mode, enter 'at' for [At Rest], 'ad' for [Adjustment],");
    Serial.println("or enter 'ex' for [Extend].") ;
    // This while loop waits for user input.
    while(Serial.available() == 0) {
    }
    argument0 = Serial.readString();
    exitArmMode = argument0;
    delay(100);
  
    if(argument0 == "ar") {
      for(int h = 220; h > 169; h--) {
        pwm.setPWM(3,0,h);
        delay(5);
      }
      pwm.setPWM(0, 0, 150);
      pwm.setPWM(1, 0, 150);

      for(int j = 320; j > 199; j--) {
        pwm.setPWM(2,0,j);
    
        delay(5);
      }
    
      delay(500);
      pwm.setPWM(4, 0, 275);
      delay(500);
    }
    else if(argument0 == "ex") {
      for(int q = 170; 99 < q; q--) {
        pwm.setPWM(3, 0, q);
        
        delay(5);
      }
      for(int x = 150; x < 171; x++) {
        pwm.setPWM(0,0,x);
        pwm.setPWM(1,0,x);
        
        delay(5); 
      }
      for(int y = 195; y < 221; y++) {
        pwm.setPWM(2,0,y);
        
        delay(5);
      }
      for(int z = 171; z < 201; z++) {
        pwm.setPWM(0, 0, z);
        pwm.setPWM(1, 0, z);
        
        delay(5);
      }
      for(int a = 221; a < 281; a++) {
        pwm.setPWM(2, 0, a);
        
        delay(5);
      }
      for(int b = 200; b < 251; b++)
      {
        pwm.setPWM(0, 0, b);
        pwm.setPWM(1, 0, b);
        
        delay(5);
      }
      for(int v = 280; v < 301; v++) {
        pwm.setPWM(2, 0, v);
        
        delay(5);
      }
      for(int c = 250; c < 301; c++) {
        pwm.setPWM(0, 0, c);
        pwm.setPWM(1, 0, c);
        
        delay(5);
      }
      for(int d = 300; d < 321; d++) {
        pwm.setPWM(2, 0, d);
        
        delay(5);
      }
      for(int e = 100; e < 221; e++) {
        pwm.setPWM(3, 0, e);
        
        delay(5);
      }
    }
    else if(argument0 == "ad") {
      // This while loop prompts the user input.
      Serial.println("Please enter Arm part: ");
      while (Serial.available() == 0) {
      }
      argument1 = Serial.readString();
      exitArmMode = argument1;
      delay(100);
      
      if(argument1 == "fi") {
        Serial.println("Please Enter tick for position from 270(close) or 300(open)");
        while (Serial.available() == 0) {
        }
        argument2 = Serial.readString();
        exitArmMode = argument2;
        tick = argument2.toInt();
      
        while(tick < 270 or tick > 300) {
          Serial.println("ERROR Please Enter tick for position for 270(close) to 300(open)");
          while (Serial.available() == 0) {
          }
          argument2 = Serial.readString();
          exitArmMode = argument2;                 
          tick = argument2.toInt();
        }
      }
      else if(argument1 == "ba") {
        Serial.println("Please Enter tick for position from 150(40°) to 450(180°)");
        while (Serial.available() == 0) {
        }
        argument2 = Serial.readString();
        exitArmMode = argument2;
        tick = argument2.toInt();
      
        while(tick < 150 or tick > 450) {
          Serial.println("ERROR Please Enter tick for position from 150(40°) to 450(180°)");
    
          while (Serial.available() == 0) {
          }
          argument2 = Serial.readString();
          exitArmMode = argument2;                 
          tick = argument2.toInt();
        }
      }
      else if(argument1 == "sh") {
        Serial.println("Please Enter tick for position from 190(40°) to 455(180°)");
        while(Serial.available() == 0) {
        }
        argument2 = Serial.readString();
        exitArmMode = argument2;
        tick = argument2.toInt();
        
        while(tick < 190 or tick > 455) {
          Serial.println("ERROR Please Enter tick for position from 190(40°) to 455(180°)");
          while (Serial.available() == 0) {
          }
          argument2 = Serial.readString();
          exitArmMode = argument2;               
          tick = argument2.toInt();
        }
      }
      else if(argument1 == "eb") {
        Serial.println("Please Enter tick for position from 100(0°) to 310(135°)");
        while (Serial.available() == 0) {  
        }
        argument2 = Serial.readString();
        exitArmMode = argument2;
        tick = argument2.toInt();
    
        while(tick < 100 or tick > 310) {
          Serial.println("ERROR Please Enter tick for position from 100(0°) to 310(135°)");
          while(Serial.available() == 0) {
          }
          argument2 = Serial.readString();
          exitArmMode = argument2;                  
          tick = argument2.toInt();
        }
      }
      else if(argument1 == "wr") {
        Serial.println("Please Enter tick for position from 100(0°) to 445(180°)");
        while(Serial.available() == 0) {
        }
        argument2 = Serial.readString();
        exitArmMode = argument2;
        tick = argument2.toInt();
        while(tick < 100 or tick > 445) {
          Serial.println("ERROR Please Enter tick for position from 100(0°) to 445(180°)");
          while(Serial.available() == 0) {
          }
          argument2 = Serial.readString();
          exitArmMode = argument2;                
          tick = argument2.toInt();
        }
      }
    }
    // Print out nicely formatted output.
    Serial.println("Part ");
    Serial.println(argument1);
    Serial.println("Tick");
    Serial.println(argument2);

    // This code sets the input from the user to the variable called 'Part'.
    Part = argument1;

    // This code is used for debug purposes.
    Serial.println(tick);
    Serial.println(Part);

    // This code calculates eventhandler information.
    if(Part == "ba") {
      pwm.setPWM(0, 0, tick);
      pwm.setPWM(1, 0, tick);
      delay(5);
    }
    if(Part == "sh") {
      pwm.setPWM(2, 0, tick);
      delay(5); 
    }
    if(Part == "eb") {
      pwm.setPWM(3, 0, tick);
      delay(5);
    }
    if(Part == "wr") {
      pwm.setPWM(4, 0, tick);
      delay(5);
    }
    if(Part == "fi") {
      pwm.setPWM(5, 0, tick);
      delay(5);
    }

    delay(500);

    if(exitArmMode == "q" || exitArmMode == "Q") {
      pwm.reset();
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


