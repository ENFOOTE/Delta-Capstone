// EE4390 EE Design I and EE4391 EE Design II
// Date created: January 25, 2016
// Programmer One: David S Vasquez
// Programmer Two: Geovanni Hernandez
// Programmer Three: Jorge Villalobos
// Programmer Four: Eric Foote

// Information: This program is being used to test a push button, the action
// of pressing the push button should enable the SPI transfer of data. 

#include <SPI.h>

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

// These integer variables are used for important SPI communications. 
int masterGreen = 7;
// int masterRed = 8;

void setup() {
  digitalWrite(slavePin, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
  // This code initializes the push-button pin as an input.
  pinMode(greenButton, INPUT);
  // pinMode(redButton, INPUT);

  attachInterrupt(digitalPinToInterrupt(greenButton), pin_ISR1, FALLING);
  // attachInterrupt(digitalPinToInterrupt(redButton), pin_ISR2, FALLING);
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

  /*if (toggle_off == true) {
    digitalWrite(slavePin, LOW);
    SPI.transfer(masterRed);
    digitalWrite(slavePin, HIGH);
  }*/
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

