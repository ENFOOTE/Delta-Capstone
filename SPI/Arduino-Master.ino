// This code is used as an example. We will include sections 
// from this code in the master source code. 

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

void setup()
{
  Serial.begin(115200);

  // This function initializes the SPI bus by setting SCK, MOSI, 
  // and SS to outputs, pulling SCK and MOSI low, and SS high. 
  SPI.begin();

  // Sets the SPI clock divider relative to the system clock, the
  // dividers available are 2, 4, 8, 16, 32, 64, or 128.
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  // These are standard declarations of the 'foo' structure member
  // variables.
  foo.a = 44;
  foo.b = 33.0;
  foo.c = 10;
}

void loop()
{
  // This function writes a 'HIGH' or a 'LOW' value to a digital
  // pin. In this case, the value is 'LOW'.
  digitalWrite(SS, LOW);

  // This function is taken from the SPI template.
  SPI_writeAnything(foo);
  digitalWrite(SS, HIGH);

  // This function delays the execution of the code in milliseconds.
  // In this case, the time delay is 1000 milliseconds or 1 second.
  delay(1000);

  // foo.c++;
}

