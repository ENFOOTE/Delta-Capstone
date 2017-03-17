// EE4390 EE Design I and EE4391 EE Design II
// Date created: January 25, 2016
// Programmer One: David S Vasquez
// Programmer Two: Geovanni Hernandez
// Programmer Three: Jorge Villalobos
// Programmer Four: Eric Foote
// Information: This program is being used to test a push button, the action
// of pressing the push button should enable the SPI transfer of data. In
// addition, this code has the GPIO communication network implemented. This
// GPIO communication network will used to communicate between the Raspberry
// Pi and the master Arduino MCU.

#include <SPI.h>

bool armGPIO_Algorithm();

// These are four input GPIO pins that will be used to receive a code from
// Raspberry Pi. Use the digitalRead() function, it returns a 0 or 1 that depends
// on if the input pin is in a HIGH state or a LOW state.
const int inputPin1_GPIO = 22;
const int inputPin2_GPIO = 23;
const int inputPin3_GPIO = 24;
const int inputPin4_GPIO = 25;

// These four integer variables will be used to store the signal sent by GPIO 
// from the Raspberry PI MCU.
int inputGPIO_Value1;
int inputGPIO_Value2;
int inputGPIO_Value3;
int inputGPIO_Value4;

// These are four output GPIO pins that will be used to send a code from 
// Arduino Mega MCU to the Raspberry Pi MCU. Use pinMode() and digitalWrite()
// to send the 4-pin command. See the Excel spreadsheet for the table of the
// codes.
const int outputPin1_GPIO = 26;
const int outputPin2_GPIO = 27;
const int outputPin3_GPIO = 28;
const int outputPin4_GPIO = 29;

// These four integer variables will be used to store the signal that will be
// sent over GPIO from the Arduino Mega MCU to the Raspberry Pi MCU.
int outputGPIO_Value1;
int outputGPIO_Value2;
int outputGPIO_Value3;
int outputGPIO_Value4;

// These are important bool variables used to execute the operation of the 
// robotic arm.
bool armExtendComplete;
bool armExtendForward;
bool armExtendBackward;
bool armCentered;
bool armShiftLeft;
bool armShiftRight;
bool grabberAligned;
bool grabberTurnCW;
bool grabberTurnCCW;

// This bool variable will be used to execute return to start position.
bool roboticArmAlgorithmComplete;

// This int variable will be used for the push button, Button1
// corresponds to 'send' button.
int greenButton = 2;
// int redButton = 3;

// This is the slave select pin.
const int slavePin = 10;

// The 'green push-button' will switch the state.
bool toggle_on = false;

// The 'red push-button' will switch the state.
// bool toggle_off = false;

// This bool variable will be used to start the GPIO robotic arm algorithm. When it
// is initialized to true, the algorithm will start. 
bool startRoboticArmAlgorithm;

// These integer variables are used for important SPI communications. 
int masterGreen = 7;
// int masterRed = 8;

void setup() {
  // This code will be used to enable the GPIO input pins that will receive a
  // 4-pin signal from the Raspberry Pi MCU.
  pinMode(inputPin1_GPIO, INPUT);
  pinMode(inputPin2_GPIO, INPUT);
  pinMode(inputPin3_GPIO, INPUT);
  pinMode(inputPin4_GPIO, INPUT);

  // This code will be used to enable the GPIO output pins that will send a
  // 4-pin signal from the Arduino Mega MCU to the Raspberry Pi MCU. 
  pinMode(outputPin1_GPIO, OUTPUT);
  pinMode(outputPin2_GPIO, OUTPUT);
  pinMode(outputPin3_GPIO, OUTPUT);
  pinMode(outputPin4_GPIO, OUTPUT):

  outputGPIO_Value1 = 0;
  outputGPIO_Value2 = 0;
  outputGPIO_Value3 = 0;
  outputGPIO_Value4 = 0;
  
  digitalWrite(slavePin, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
  // This code initializes the push-button pin as an input.
  pinMode(greenButton, INPUT);
  // pinMode(redButton, INPUT);

  attachInterrupt(digitalPinToInterrupt(greenButton), pin_ISR1, FALLING);
  // attachInterrupt(digitalPinToInterrupt(redButton), pin_ISR2, FALLING);

  startRoboticArmAlgorithm = false;
  roboticArmAlgorithmComplete = false;
  
}

// This function will send an integer value to slave board. In addition,
// the function will use a delay to wait for a response from the slave board.
int transferAndWait(const int masterCommand) {
  int slaveReply = SPI.transfer(masterCommand);

  delayMicroseconds(20);

  return slaveReply;
}

void loop() {
  if (toggle_on == true) {
    digitalWrite(slavePin, LOW);
    transferAndWait(masterGreen);
    digitalWrite(slavePin, HIGH);
  }

  /*
  if (toggle_off == true) {
    digitalWrite(slavePin, LOW);
    SPI.transfer(masterRed);
    digitalWrite(slavePin, HIGH);
  }
  */

  roboticArmAlgorithmComplete = armGPIO_Algorithm();
}

// This interrupt function is for the push button.
void pin_ISR1() 
{
  static unsigned long last_interrupt_time1 = 0;

  // The 'millis' function returns the number of milliseconds since the
  // Arduino board began running the current program.
  unsigned long interrupt_time1 = millis();
  
  // After a certain amount of time, it will toggle on.
  if (interrupt_time1 - last_interrupt_time1 > 200)
  {
    toggle_on = true;
    last_interrupt_time1 = interrupt_time1;
  }
}

/*
void pin_ISR2() 
{
   masterGreen = 0;
  
  static unsigned long last_interrupt_time2 = 0;

  // The 'millis' function returns the number of milliseconds since the
  // Arduino board began running the current program.
  unsigned long interrupt_time2 = millis();
  
  // After a certain amount of time, it will toggle on.
  if (interrupt_time2 - last_interrupt_time2 > 200)
  {
    toggle_off = true;
    last_interrupt_time2 = interrupt_time2;
  }
}*/

// This function is the robotic arm algorithm. It uses 2 sets of 4-pin signals going 
// to and from the Arduino Mega MCU and the Raspberry Pi MCU.
bool armGPIO_Algorithm() {
  // This initialization is the 'start camera' signal to the Raspberry Pi.
  outputGPIO_Value1 = 0;
  outputGPIO_Value2 = 1;
  outputGPIO_Value3 = 1;
  outputGPIO_Value4 = 1;

  // These digital write statements send a signal to the Raspberry Pi to start
  // the camera.
  digitalWrite(outputPin1_GPIO, outputGPIO_Value1);
  digitalWrite(outputPin2_GPIO, outputGPIO_Value2);
  digitalWrite(outputPin3_GPIO, outputGPIO_Value3);
  digitalWrite(outputPin4_GPIO, outputGPIO_Value4);

  startRoboticArmAlgorithm = true;
  
  while(startRoboticArmAlgorithm == true) {
    // robotic arm code to extend arm forward

    delay(10);

    // This code reads the response from the Raspberry Pi. 
    inputValue1 = digitalRead(inputPin1_GPIO);
    inputValue2 = digitalRead(inputPin2_GPIO);
    inputValue3 = digitalRead(inputPin3_GPIO);
    inputValue4 = digitalRead(inputPin4_GPIO);

    if(inputValue4 == 0 && inputValue3 == 0 && inputValue2 == 0 && inputValue1 == 1) {
      armExtendComplete = true;
    }
    if(inputValue4 == 0 && inputValue3 == 0 && inputValue2 == 1 && inputValue1 == 0) {
      armExtendForward = true;
    }
    if(inputValue4 == 0 && inputValue3 == 0 && inputValue2 == 1 && inputValue1 == 1) {
      armExtendBackward = true;
    }
    if(inputValue4 == 0 && inputValue3 == 1 && inputValue2 == 0 && inputValue1 == 0) {
      armCentered = true;
    }
    if(inputValue4 == 0 && inputValue3 == 1 && inputValue2 == 0 && inputValue1 == 1) {
      armShiftLeft = true;
    }
    if(inputValue4 == 0 && inputValue3 == 1 && inputValue2 == 1 && inputValue1 == 0) {
      armShiftRight = true;
    }
    if(inputValue4 == 0 && inputValue3 == 1 && inputValue2 == 1 && inputValue1 == 1) {
      grabberAligned = true;
    }
    if(inputValue4 == 1 && inputValue3 == 0 && inputValue2 == 0 && inputValue1 == 0) {
      grabberTurnCW = true;
    }
    if(inputValue4 == 1 && inputValue3 == 0 && inputValue2 == 0 && inputValue1 == 1) {
      grabberTurnCCW = true;
    }

    while(armExtendForward == true) {
      // execute the code that extends the robotic arm forward

      // These initializations represent that the 'recent arm movement' is complete.
      outputGPIO_Value4 = 0;
      outputGPIO_Value3 = 0;
      outputGPIO_Value2 = 1;
      outputGPIO_Value1 = 1;

      // This code sends a signal to the Raspberry Pi telling it that the extend forward
      // command has been completed.
      digitalWrite(outputPin1_GPIO, outputGPIO_Value1);
      digitalWrite(outputPin2_GPIO, outputGPIO_Value2);
      digitalWrite(outputPin3_GPIO, outputGPIO_Value3);
      digitalWrite(outputPin4_GPIO, outputGPIO_Value4);
      
      delay(10);

      // These initializations represent the response from the Raspberry Pi.
      inputValue1 = digitalRead(inputPin1_GPIO);
      inputValue2 = digitalRead(inputPin2_GPIO);
      inputValue3 = digitalRead(inputPin3_GPIO);
      inputValue4 = digitalRead(inputPin4_GPIO);

      // This if statement checks if further forward extension is required for the robotic
      // arm. 
      if(inputValue4 == 0 && inputValue3 == 0 && inputValue2 == 1 && inputValue1 == 0) {
        armExtendForward = true;
      }
      else {
        armExtendForward = false;
      }    
    }
    
    while(armExtendBackward == true) {
      // execute the code that extends the robotic arm backwards

      // These initializations represent that the 'recent arm movement' is complete.
      outputGPIO_Value4 = 0;
      outputGPIO_Value3 = 0;
      outputGPIO_Value2 = 1;
      outputGPIO_Value1 = 1;

      // This code sends a signal to the Raspberry Pi telling it that the extend forward
      // command has been completed.
      digitalWrite(outputPin1_GPIO, outputGPIO_Value1);
      digitalWrite(outputPin2_GPIO, outputGPIO_Value2);
      digitalWrite(outputPin3_GPIO, outputGPIO_Value3);
      digitalWrite(outputPin4_GPIO, outputGPIO_Value4);
      
      delay(10);

      // These initializations represent the response from the Raspberry Pi.
      inputValue1 = digitalRead(inputPin1_GPIO);
      inputValue2 = digitalRead(inputPin2_GPIO);
      inputValue3 = digitalRead(inputPin3_GPIO);
      inputValue4 = digitalRead(inputPin4_GPIO);

      // This if statement checks if further backward extension is required for the robotic
      // arm.
      if(inputValue4 == 0 && inputValue3 == 0 && inputValue2 == 1 && inputValue1 == 1) {
        armExtendBackward = true;
      }
      else {
        armExtendBackward = false;   
      }
    }
    
    while(armExtendComplete == true && armShiftLeft == true) {
      // robotic arm code to shift the it to the left

      // These initializations represent that the 'recent arm movement' is complete.
      outputGPIO_Value4 = 0;
      outputGPIO_Value3 = 0;
      outputGPIO_Value2 = 1;
      outputGPIO_Value1 = 1;

      // This code sends a signal to the Raspberry Pi telling it that the shift left
      // command has been completed.
      digitalWrite(outputPin1_GPIO, outputGPIO_Value1);
      digitalWrite(outputPin2_GPIO, outputGPIO_Value2);
      digitalWrite(outputPin3_GPIO, outputGPIO_Value3);
      digitalWrite(outputPin4_GPIO, outputGPIO_Value4);
      
      delay(10);

      // These initializations represent the response from the Raspberry Pi.
      inputValue1 = digitalRead(inputPin1_GPIO);
      inputValue2 = digitalRead(inputPin2_GPIO);
      inputValue3 = digitalRead(inputPin3_GPIO);
      inputValue4 = digitalRead(inputPin4_GPIO);      

      // This if statement checks if the arm requires more shift to the left for the 
      // robotic arm.
      if(inputValue4 == 0 && inputValue3 == 1 && inputValue2 == 0 && inputValue1 == 1) {
        armShiftLeft = true;
      }
      else {
        armShiftLeft = false;
      }
    }

    while(armExtendComplete == true && armShiftRight == true) {
      // robotic arm code to shift the it to the right

      // These initializations represent that the 'recent arm movement' is complete.
      outputGPIO_Value4 = 0;
      outputGPIO_Value3 = 0;
      outputGPIO_Value2 = 1;
      outputGPIO_Value1 = 1;

      // This code sends a signal to the Raspberry Pi telling it that the shift right
      // command has been completed.
      digitalWrite(outputPin1_GPIO, outputGPIO_Value1);
      digitalWrite(outputPin2_GPIO, outputGPIO_Value2);
      digitalWrite(outputPin3_GPIO, outputGPIO_Value3);
      digitalWrite(outputPin4_GPIO, outputGPIO_Value4);
      
      delay(10);

      // These initializations represent the response from the Raspberry Pi.
      inputValue1 = digitalRead(inputPin1_GPIO);
      inputValue2 = digitalRead(inputPin2_GPIO);
      inputValue3 = digitalRead(inputPin3_GPIO);
      inputValue4 = digitalRead(inputPin4_GPIO);      

      // This if statement checks if the arm requires more shift to the right for the 
      // robotic arm.
      if(inputValue4 == 0 && inputValue3 == 1 && inputValue2 == 1 && inputValue1 == 0) {
        armShiftRight = true;
      }
      else {
        armShiftRight = false;
      }
    }

    while(armExtendComplete == true && armCentered == true && grabberTurnCW == true) {
      // robotic arm code to turn the grabber clockwise

      // These initializations represent that the 'recent arm movement' is complete.
      outputGPIO_Value4 = 0;
      outputGPIO_Value3 = 0;
      outputGPIO_Value2 = 1;
      outputGPIO_Value1 = 1;

      // This code sends a signal to the Raspberry Pi telling it that the grabber 
      // clockwise turn command has been completed.
      digitalWrite(outputPin1_GPIO, outputGPIO_Value1);
      digitalWrite(outputPin2_GPIO, outputGPIO_Value2);
      digitalWrite(outputPin3_GPIO, outputGPIO_Value3);
      digitalWrite(outputPin4_GPIO, outputGPIO_Value4);
      
      delay(10);

      // These initializations represent the response from the Raspberry Pi.
      inputValue1 = digitalRead(inputPin1_GPIO);
      inputValue2 = digitalRead(inputPin2_GPIO);
      inputValue3 = digitalRead(inputPin3_GPIO);
      inputValue4 = digitalRead(inputPin4_GPIO);      

      // This if statement checks if the grabber requires additional clockwise rotation.
      if(inputValue4 == 1 && inputValue3 == 0 && inputValue2 == 0 && inputValue1 == 0) {
        grabberTurnCW = true;
      }
      else {
        grabberTurnCW = false;
      }
    }

    while(armExtendComplete == true && armCentered == true && grabberTurnCCW == true) {
      // robotic arm code to turn the grabber clockwise

      // These initializations represent that the 'recent arm movement' is complete.
      outputGPIO_Value4 = 0;
      outputGPIO_Value3 = 0;
      outputGPIO_Value2 = 1;
      outputGPIO_Value1 = 1;

      // This code sends a signal to the Raspberry Pi telling it that the grabber 
      // counter-clockwise turn command has been completed.
      digitalWrite(outputPin1_GPIO, outputGPIO_Value1);
      digitalWrite(outputPin2_GPIO, outputGPIO_Value2);
      digitalWrite(outputPin3_GPIO, outputGPIO_Value3);
      digitalWrite(outputPin4_GPIO, outputGPIO_Value4);
      
      delay(10);

      // These initializations represent the response from the Raspberry Pi.
      inputValue1 = digitalRead(inputPin1_GPIO);
      inputValue2 = digitalRead(inputPin2_GPIO);
      inputValue3 = digitalRead(inputPin3_GPIO);
      inputValue4 = digitalRead(inputPin4_GPIO);      

      // This if statement checks if the grabber requires additional counter-clockwise 
      // rotation.
      if(inputValue4 == 1 && inputValue3 == 0 && inputValue2 == 0 && inputValue1 == 1) {
        grabberTurnCCW = true;
      }
      else {
        grabberTurnCCW = false;
      }
    }

    if(armExtendComplete == true && armCentered == true && grabberAligned == true) {
      // robotic code that deploys the grabber

      // These initializations represent the 'request for die detection' signal.
      outputGPIO_Value4 = 1;
      outputGPIO_Value3 = 1;
      outputGPIO_Value2 = 1;
      outputGPIO_Value1 = 1;

      // This code sends the command to the Raspberry Pi.
      digitalWrite(outputPin1_GPIO, outputGPIO_Value1);
      digitalWrite(outputPin2_GPIO, outputGPIO_Value2);
      digitalWrite(outputPin3_GPIO, outputGPIO_Value3);
      digitalWrite(outputPin4_GPIO, outputGPIO_Value4);
      
      delay(10);

      // These initializations represent the response from the Raspberry Pi.
      inputValue1 = digitalRead(inputPin1_GPIO);
      inputValue2 = digitalRead(inputPin2_GPIO);
      inputValue3 = digitalRead(inputPin3_GPIO);
      inputValue4 = digitalRead(inputPin4_GPIO);      

      // This if statement checks if the camera was able to capture the die value.
      if(inputValue4 == 1 && inputValue3 == 0 && inputValue2 == 1 && inputValue1 == 0) {
        startRoboticArmAlgorithm = false;
      }      
    }
  }

  return true;
}

