#include <SPI.h>
#include "SPI_Template.h"

// This is a standard structure.
// We will use this 'myStruct' structure to 
// transfer data from the master Arduino unit
// to the slave unit. 
typedef struct myStruct
{
  int a;
  float b;
  long c;
};

// This is a structure object, in this case, we
// called it 'foo'.
myStruct foo;
bool haveData = false;

// This int variable is used to test the SPI transfer.
int ledPin = 7;

void setup()
{
  Serial.begin(115200);

  // This pin enables master input and slave output.
  pinMode(MISO, OUTPUT);
  
  // SPI Control Register, turns on SPI in slave mode.
  SPCR |= _BV(SPE);

  // This function turns on the interrupt.
  SPI.attachInterrupt();

  // This function configures the specified pin to behave either as an 
  // input or an output.
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (haveData)
  {
    // This outputs values to the console as a test.
    Serial.println(foo.a);
    Serial.println(foo.b);
    Serial.println(foo.c);
    Serial.println();

    if(foo.b = 32.0)
    {
      Serial.println();
      Serial.println("Successful SPI.");
      Serial.println();

      for(int i = 1; i < 10; i++)
      {
        // This function writes a 'HIGH' or a 'LOW' value to a digital
        // pin. In this case, the value is 'LOW'.
        digitalWrite(ledPin, HIGH);

        // This function delays the execution of the code in milliseconds.
        // In this case, the time delay is 1000 milliseconds or 1 second.    
        delay(1000);
        digitalWrite(ledPin, LOW);
        delay(1000);
      }
    }
    else
    {
      Serial.println("Failed to communicate.");
    }
  }
}

// This function is the SPI interrupt service routine.
ISR (SPI_STC_vect)
{
  SPI_readAnything_ISR(foo);
  haveData = true;
}

