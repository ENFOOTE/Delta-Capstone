// EE4390 EE Design I and EE4391 EE Design II
// Date created: November 26, 2016 
// Programmer One: David S Vasquez
// Programmer Two: Eric Foote
// Programmer Three: Jorge Villalobos
// Information: This is the master code program for the Mega Arduino 
// board. The program will have the mapping algorithm. This algorithm
// will map the entire tunnel including the extension cable and the
// dead-end tunnel. In addition, this program will have the code for
// the start button and the stop button.

// These two libraries are using for the SPI template code.
#include <SPI.h>
#include "SPI_Template.h"





// This structure is for the SPI communication. The programmers can
// create custom structure objects to fit the needs of the program.
typedef struct myStruct {
  int a;
  float b;
  long c;
};

// This structure object corresponds to the 'green start push button'.
myStruct grnButton;

// This structure object corresponds to the 'red stop push button'.
myStruct redButton;

// These int variables will used for the two push buttons, 'button1'
// corresponds to the 'green start push button' and 'button2 corresponds
// to the 'red stop push button'. The value '2' corresponds to digital
// input 2 and value '3' corresponds to digital input 3.
int button1 = 2;
int button2 = 3;

// This int variable is the action of the pressing of button and it 
// will be used to switch the state of a button.
int toggle_on; 

// This void function is used to setup important features
// of the Arduino microprocessor board.
void setup() {
  Serial.begin(115200);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  grnButton.a = 7;
  redButton.b = 8;

  // This code below initializes the two push-button pins as an inputs.
  // In addition, the 'attachInterrupt' function initializes the 
  // interrupts for both pins.
  pinMode(button1, INPUT);
  attachInterrupt(digitalPinToInterrupt(button1), pin_ISR1, FALLING);
  pinMode(button2, INPUT);
  attachInterrupt(digitalPinToInterrupt(button2), pin_ISR2, RISING);
  
}

// This void function acts just like the main function.
void loop() {
  // This if statement sends the 'green button' struct object using
  // SPI to the MUC that uses the motor encoder code.
  if (toggle_on == 1) {
    digitalWrite(SS, LOW);
    SPI_writeAnything(grnButton);
    digitalWrite(SS, HIGH);

    delay(1000);
  }
  // This if statement sends the 'green button' struct object using
  // SPI to the MUC that uses the motor encoder code.
  if(toggle_on == 0) {
    digitalWrite(SS, LOW);
    SPI_writeAnything(structComm2);
    digitalWrite(SS, HIGH);
  }  
}

// This function serves as an interrupt for the 'green start' button.
void pin_ISR1() 
{
  static unsigned long last_interrupt_time1 = 0;

  unsigned long interrupt_time1 = millis();
  
  // After a certain amount of time, it will toggle on.
  if (interrupt_time1 - last_interrupt_time1 > 200)
  {
    toggle_on = 1;
  }
  
  last_interrupt_time1 = interrupt_time1;
}

// This function serves as an interrupt for the 'red stop' button.
void pin_ISR2()
{
  static unsigned long last_interrupt_time2 = 0;

  // After a certain of time, it will toggle off. 
  unsigned long interrupt_time2 = millis();
  
  if (interrupt_time2 - last_interrupt_time2 > 200)
  {
    toggle_on = 0;
  }
  
  last_interrupt_time2 = interrupt_time2;
}


