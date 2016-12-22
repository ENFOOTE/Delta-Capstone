// EE4390 EE Design I
// Date created: December 19, 2016 
// Author One: Jorge Villalobos
// Author Two: David Silvino Vasquez
// Author Three: Eric Foote
// Information: This is an implementation file for the LED array. 
// This code was taken directly from code that Jorge wrote.

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"
#include "ArrayLED.h"

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 6, 
	NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
	NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
	NEO_GRB + NEO_KHZ800);
	
ArrayLED::ArrayLED() {
	/*
	argColor = "y";
	argLocation = "A7"
	
	x = 0;
	y = 7;
	*/
}
void ArrayLight::setLocation() {
	
}
		
void ArrayLight::setColor() {
	
}
		
void ArrayLight::lightLED() {
	if(argument2 == "r")                     // Color RED
{
  if(argument1 == "A1")                  //Locations
    {
      x=0;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }
   
    
    else if(argument1 == "A2")
    {
       x=0;
       y=1;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }
 
    else if(argument1 == "A3")
    {
      x=0;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1=="A4")
    {
      x=0;
      y=3;
      matrix.drawPixel(0,3,matrix.Color(red.r, red.g, red.b));
      matrix.show();
      
    }

    else if(argument1 == "A5")
    {
      x=0;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "A6")
    {
       x=0;
       y=5;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "A7")
    {
      x=0;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "B1")
    {
      x=1;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "B2")
    {
      x=1;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "B3")
    {
      x=1;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "B4")
    {
      x=1;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "B5")
    {
      x=1;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "B6")
    {
      x=1;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "B7")
    {
      x=1;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "C1")
    {
      x=2;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "C2")
    {
      x=2;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "C3")
    {
      x=2;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "C4")
    {
      x=2;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "C5")
    {
      x=2;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "C6")
    {
      x=2;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "C7")
    {
      x=2;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "D1")
    {
      x=3;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "D2")
    {
      x=3;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "D3")
    {
      x=3;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "D4")
    {
      x=3;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "D5")
    {
      x=3;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "D6")
    {
      x=3;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "D7")
    {
      x=3;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "E1")
    {
      x=4;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "E2")
    {
      x=4;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "E3")
    {
      x=4;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "E4")
    {
      x=4;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "E5")
    {
      x=4;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "E6")
    {
      x=4;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "E7")
    {
      x=4;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "F1")
    {
      x=5;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "F2")
    {
      x=5;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "F3")
    {
      x=5;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "F4")
    {
      x=5;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "F5")
    {
      x=5;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }
 
    else if(argument1 == "F6")
    {
      x=5;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "F7")
    {
      x=5;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }
 
    else if(argument1 == "G1")
    {
      x=6;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "G2")
    {
      x=6;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "G3")
    {
      x=6;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "G4")
    {
      x=6;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }
 
    else if(argument1 == "G5")
    {
      x=6;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }
 
    else if(argument1 == "G6")
    {
      x=6;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "G7")
    {
      x=6;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

  }
  

else if(argument2 == "b")                       //Color BLUE
    {
   if(argument1 == "A1")                        //Locations
    {
      x=0;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }
   
    
    else if(argument1 == "A2")
    {
       x=0;
       y=1;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }
 
    else if(argument1 == "A3")
    {
      x=0;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1=="A4")
    {
      x=0;
      y=3;
      matrix.drawPixel(0,3,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
      
    }

    else if(argument1 == "A5")
    {
      x=0;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "A6")
    {
       x=0;
       y=5;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "A7")
    {
      x=0;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "B1")
    {
      x=1;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "B2")
    {
      x=1;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(red.r, red.g, red.b));
      matrix.show();
    }

    else if(argument1 == "B3")
    {
      x=1;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "B4")
    {
      x=1;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "B5")
    {
      x=1;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "B6")
    {
      x=1;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "B7")
    {
      x=1;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "C1")
    {
      x=2;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "C2")
    {
      x=2;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "C3")
    {
      x=2;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "C4")
    {
      x=2;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "C5")
    {
      x=2;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "C6")
    {
      x=2;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "C7")
    {
      x=2;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "D1")
    {
      x=3;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "D2")
    {
      x=3;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "D3")
    {
      x=3;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "D4")
    {
      x=3;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "D5")
    {
      x=3;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "D6")
    {
      x=3;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "D7")
    {
      x=3;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "E1")
    {
      x=4;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "E2")
    {
      x=4;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "E3")
    {
      x=4;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "E4")
    {
      x=4;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "E5")
    {
      x=4;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "E6")
    {
      x=4;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "E7")
    {
      x=4;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "F1")
    {
      x=5;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "F2")
    {
      x=5;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "F3")
    {
      x=5;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "F4")
    {
      x=5;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "F5")
    {
      x=5;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }
 
    else if(argument1 == "F6")
    {
      x=5;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "F7")
    {
      x=5;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }
 
    else if(argument1 == "G1")
    {
      x=6;
      y=0;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "G2")
    {
      x=6;
      y=1;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "G3")
    {
      x=6;
      y=2;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "G4")
    {
      x=6;
      y=3;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }
 
    else if(argument1 == "G5")
    {
      x=6;
      y=4;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }
 
    else if(argument1 == "G6")
    {
      x=6;
      y=5;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

    else if(argument1 == "G7")
    {
      x=6;
      y=6;
      matrix.drawPixel(x,y,matrix.Color(blue.r, blue.g, blue.b));
      matrix.show();
    }

  }
  matrix.drawPixel(0,6,matrix.Color(yellow.r,yellow.g,yellow.b)); // Color yellow for A7
  matrix.show();                                                  // Shows it all onto the matrix.

	
	
}