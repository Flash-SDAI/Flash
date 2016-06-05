/**
* Flasher.cpp
* Purpose: The class represents multy task work in the
* arduino environment. It's purpose is two flash an LED.
* @author Stoian Ianev
* @version 1.0 6/06/16
*/

#include "Flasher.h"
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Constructor - creates a Flasher 
// and initializes the member variables and state
Flasher::Flasher(int pin, long on, long off){
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  onTime = on;
  offTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
}
 
/**
* The function starts the flashing of the LED. The flashing is done depending on
* the current time and the previous time interval from the last flash.
*/
void Flasher::startFlashing(){
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();
   
  if((ledState == HIGH) && (currentMillis - previousMillis >= onTime))
  {
    changeState(LOW, currentMillis);
  }
  else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime))
  {
    changeState(HIGH, currentMillis);
  }
}

/**
* The functions assigns LOW value to the state of the LED and stops the flashing.
*/
void Flasher::stopFlashing(){
  changeState(LOW, offTime);
}

/**
* The function makes prevous time to be equal to 
* current time. Also changes the state of the LED. From HIGH to LOW and
* vice versa.
*/
void Flasher::changeState(int state, long currentMillis){
  ledState = state;  // change led state
  previousMillis = currentMillis;   // Remember the time
  digitalWrite(ledPin, ledState);   // Update the actual LED
}