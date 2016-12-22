// EE4390 EE Design I
// Date created: December 19, 2016 
// Author One: Jorge Villalobos
// Author Two: David Silvino Vasquez
// Author Three: Eric Foote
// Information: This is a header file for the LED array. 
// This code was taken directly from code that Jorge wrote.

#ifndef ARRAYLED_H
#define ARRAYLED_H

class ArrayLight {
	private:
		// These integers variables are used for the matrix constructor.
		int x;
		int y;
		
		// The location of the LED array.
		String argLocation;
		// The color of the LED that will be turned on. 
		String argColor;
	
	public:
		ArrayLight();
		setLocation();
		setColor();
		lightLED(); 
}