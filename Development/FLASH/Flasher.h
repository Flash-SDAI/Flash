/**
* Flasher.h
* Purpose: This is the interface for Flasher.cpp.
* @author Stoian Ianev
* @version 1.0 6/06/16
*/

#ifndef ADD_H
#define ADD_H

class Flasher{
  // Class Member Variables
  // These are initialized at startup
  private:
  int ledPin;      // the number of the LED pin
  long onTime;     // milliseconds of on-time
  long offTime;    // milliseconds of off-time
 
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated
	
  public:
  //Constructor
	Flasher(int pin, long on, long off);
	/**
    * The function starts the flashing of the LED.
    */
	void startFlashing();
	/**
    * The functions stops the flashing of the LED.
    */
	void stopFlashing();
		
  private:
    /**
    * Changes the state of the LED. From HIGH to LOW and
    * vice versa.
    */
	void changeState(int state, long currentMillis);
};
#endif
