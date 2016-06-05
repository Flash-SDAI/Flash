#include "Flasher.h"

//Constants
const int TURN_LIGHT_FLASH_DURATION = 500;
const int PHOTO_RESISTOR_WORKING_VALUE = 100;

const int PHOTO_RESISTOR_PIN = A0;

const int SHORT_LIGHTS_PIN = 13;
const int LONG_LIGHTS_PIN = 12;
const int RIGHT_TURN_SIGNAL_PIN = 11;
const int LEFT_TURN_SIGNAL_PIN = 10;
const int STOP_LIGHTS_PIN = 9;

const int HEAD_LIGHTS_BTN_PIN_ONE = 8;
const int HEAD_LIGHTS_BTN_PIN_TWO = 7;
const int RIGHT_TURN_LIGHTS_BTN_PIN = 6;
const int LEFT_TURN_LIGHTS_BTN_PIN = 5;
const int EMERGENCY_LIGHTS_BTN_PIN = 4;
const int STOP_LIGHTS_BTN_PIN = 3;

//Local values
int photoResistorValue = 0;
bool isInEmergencyMode = false;
bool isInAutoLightMode = false;

//Used for blinking effect of the LEDs
Flasher leftTurnSignal(LEFT_TURN_SIGNAL_PIN, TURN_LIGHT_FLASH_DURATION, TURN_LIGHT_FLASH_DURATION);
Flasher rightTurnSignal(RIGHT_TURN_SIGNAL_PIN, TURN_LIGHT_FLASH_DURATION, TURN_LIGHT_FLASH_DURATION);

/**
 * The setup function where the input and output pins are initialized.
 */
void setup() {
  Serial.begin(9600);
  // initialize photo resistor pin
  pinMode(PHOTO_RESISTOR_PIN, INPUT);
  // initialize diod pins
  pinMode(SHORT_LIGHTS_PIN, OUTPUT);
  pinMode(LONG_LIGHTS_PIN, OUTPUT);
  pinMode(STOP_LIGHTS_PIN, OUTPUT);
  // initialize btn pins
  pinMode(HEAD_LIGHTS_BTN_PIN_ONE, INPUT);
  pinMode(HEAD_LIGHTS_BTN_PIN_TWO, INPUT);
  pinMode(RIGHT_TURN_LIGHTS_BTN_PIN, INPUT);
  pinMode(LEFT_TURN_LIGHTS_BTN_PIN, INPUT);
  pinMode(EMERGENCY_LIGHTS_BTN_PIN, INPUT);
  pinMode(STOP_LIGHTS_BTN_PIN, INPUT);
}

/**
 * The loop function runs over and over again forever.
 */
void loop() { 
  lightDetection();
  headLights();
  turnLights();
  emergencyLights();
  stopLights();
}

/**
 * This function detects the level of light using the input data from a photoresistor.
 * If the value from the photoresistor is lower or equal than PHOTO_RESISTOR_WORKING_VALUE
 * the lights of the car will be switched on.
 */
void lightDetection(){
  photoResistorValue = analogRead(PHOTO_RESISTOR_PIN);
  if(photoResistorValue <= PHOTO_RESISTOR_WORKING_VALUE){
    isInAutoLightMode = true;
    digitalWrite(SHORT_LIGHTS_PIN, HIGH); 
  }else{
    if(isInAutoLightMode){
      isInAutoLightMode = false;
    }
  }
}

/**
 * This function is controling the short and long lights of the car, depending on the state 
 * of the 3 way switch.
 * Left State - OFF
 * Middle State - SHORT LIGHTS
 * Right State - SHORT & LONG LIGHTS
 */
void headLights(){ 
  if(!isInAutoLightMode){
    if(digitalRead(HEAD_LIGHTS_BTN_PIN_ONE) == HIGH){
      digitalWrite(SHORT_LIGHTS_PIN, LOW); 
      digitalWrite(LONG_LIGHTS_PIN, LOW);
    }else if(digitalRead(HEAD_LIGHTS_BTN_PIN_ONE) == LOW && digitalRead(HEAD_LIGHTS_BTN_PIN_TWO) == LOW){
      digitalWrite(SHORT_LIGHTS_PIN, HIGH); 
      digitalWrite(LONG_LIGHTS_PIN, LOW);
    }else{
      digitalWrite(SHORT_LIGHTS_PIN, HIGH); 
      digitalWrite(LONG_LIGHTS_PIN, HIGH);
    }
  }else{
    if(digitalRead(HEAD_LIGHTS_BTN_PIN_TWO) == HIGH){
     digitalWrite(LONG_LIGHTS_PIN, HIGH); 
    }else{
      digitalWrite(LONG_LIGHTS_PIN, LOW);
   }
  }
}

/**
 * The function is controling the turn lights of the car(with blink effect), 
 * depending on the state of the 3 way switch.
 * Left State - Left Turn Lights 
 * Middle State - OFF
 * Right State - Right Turn Lights
 */
void turnLights(){
  if(!isInEmergencyMode){
    if(digitalRead(RIGHT_TURN_LIGHTS_BTN_PIN)== HIGH){
      leftTurnSignal.startFlashing();
    }else{
      leftTurnSignal.stopFlashing();
    }
    if(digitalRead(LEFT_TURN_LIGHTS_BTN_PIN) == HIGH){
      rightTurnSignal.startFlashing();
    }else{
      rightTurnSignal.stopFlashing();
    }
  }
}

/**
 * The function is controling the emergency lights of the car(with blink effect). They are
 * with highe preority of the turn lights and have two states - ON and OFF.
 */
void emergencyLights(){
  if(digitalRead(EMERGENCY_LIGHTS_BTN_PIN) == HIGH){
    if(!isInEmergencyMode){
      isInEmergencyMode = true;
      leftTurnSignal.stopFlashing();
      rightTurnSignal.stopFlashing();
    }
    leftTurnSignal.startFlashing();
    rightTurnSignal.startFlashing();
  }else{
    if(isInEmergencyMode){
      isInEmergencyMode = false;
      leftTurnSignal.stopFlashing();
      rightTurnSignal.stopFlashing();
    }
  }
}

/**
 * This function is controling the stop lights of the car.
 * As long as the break of the car is pressed the light will be ON.
 * Other ways they are OFF.
 */
void stopLights(){
  if(digitalRead(STOP_LIGHTS_BTN_PIN) == HIGH){
    digitalWrite(STOP_LIGHTS_PIN, HIGH);
  }else{
    digitalWrite(STOP_LIGHTS_PIN, LOW);
  }
}

