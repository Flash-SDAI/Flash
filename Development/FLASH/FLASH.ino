class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  private:
  int ledPin;      // the number of the LED pin
  long onTime;     // milliseconds of on-time
  long offTime;    // milliseconds of off-time
 
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated
 
  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off){
    ledPin = pin;
    pinMode(ledPin, OUTPUT);     
    
    onTime = on;
    offTime = off;
  
    ledState = LOW; 
    previousMillis = 0;
  }
 
  void startFlashing(){
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

  void stopFlashing(){
    changeState(LOW, offTime);
  }

  private:
  void changeState(int state, long currentMillis){
    ledState = state;  // change led state
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(ledPin, ledState);   // Update the actual LED
  }
};

class BtnState
{
  private:
  int old_val;
  int numOfStates;
  unsigned long previousMillis;
  public:
  const int COUNTER_UNDEFINED = -1;
  int btnState;
  int btnCounterState;

  BtnState(){
    old_val = 0;
    previousMillis = 0;
    btnState = 0;
    btnCounterState = -1;
  }

  BtnState(int statesCounter) : BtnState(){
    numOfStates = statesCounter;
  }

  void changeState(int readState){
    unsigned long currentMillis = millis();
    if((readState == HIGH) && (old_val == LOW) && (currentMillis - previousMillis >= 200)){
      btnState = 1- btnState;
      if(numOfStates != COUNTER_UNDEFINED){
        ++btnCounterState;
        if(btnCounterState % numOfStates == 0){
          btnCounterState = 0;
        }
      }
      previousMillis = currentMillis;
    }
    old_val = readState;
  }

  void resetStateCounter(){
    btnCounterState = -1;
  }
};

const int turnLightFlashDuration = 500;
const int photoResistorWorkingValue = 100;

const int photoResistorPin = A0;

const int shortLightsPin = 13;
const int longLightsPin = 12;
const int leftTurnSignalPin = 11;
const int rightTurnSignalPin = 10;
const int stopLightsPin = 9;

const int headLightsBtnPin = 8;
const int turnLightsBtnPin = 7;
const int emergencyLightsBtnPin = 6;
const int stopLightsBtnPin = 5;

int photoResistorValue = 0;
bool isInEmergencyMode = false;
bool isInAutoLightMode = false;

BtnState headLightsBtnState(4);
BtnState turnLightsBtnState(4);
BtnState emergencyLightsBtnState(2);

Flasher leftTurnSignal(leftTurnSignalPin, turnLightFlashDuration, turnLightFlashDuration);
Flasher rightTurnSignal(rightTurnSignalPin, turnLightFlashDuration, turnLightFlashDuration);
Flasher emergencyLeftSignal(leftTurnSignalPin, turnLightFlashDuration, turnLightFlashDuration);
Flasher emergencyRightSignal(rightTurnSignalPin, turnLightFlashDuration, turnLightFlashDuration);

void setup() {
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  pinMode(photoResistorPin, INPUT);
  
  pinMode(shortLightsPin, OUTPUT);
  pinMode(longLightsPin, OUTPUT);
  pinMode(stopLightsPin, OUTPUT);
  
  pinMode(headLightsBtnPin, INPUT);
  pinMode(turnLightsBtnPin, INPUT);
  pinMode(emergencyLightsBtnPin, INPUT);
  pinMode(stopLightsBtnPin, INPUT);
}

// the loop function runs over and over again forever
void loop() { 
  lightDetection();
  headLights();
  turnLights();
  emergencyLights();
  stopLights();
}

void lightDetection(){
  photoResistorValue = analogRead(photoResistorPin);
  if(photoResistorValue <= photoResistorWorkingValue){
    isInAutoLightMode = true;
    digitalWrite(shortLightsPin, HIGH); 
  }else{
    if(isInAutoLightMode){
      isInAutoLightMode = false;
      headLightsBtnState.resetStateCounter();
    }
  }
}

void headLights(){ 
  headLightsBtnState.changeState(digitalRead(headLightsBtnPin));
  if(!isInAutoLightMode){
    switch(headLightsBtnState.btnCounterState){
      case 0:
        digitalWrite(shortLightsPin, HIGH); 
      break;
      case 1:
        digitalWrite(shortLightsPin, HIGH); 
        digitalWrite(longLightsPin, HIGH);    
      break;
      case 2:
        digitalWrite(shortLightsPin, HIGH); 
        digitalWrite(longLightsPin, LOW);
      break;
      case 3:     
      default:
        digitalWrite(longLightsPin, LOW);
        digitalWrite(shortLightsPin, LOW);
      break;
    }
  }else{
    if(headLightsBtnState.btnState == HIGH){
      digitalWrite(longLightsPin, HIGH); 
    }else{
      digitalWrite(longLightsPin, LOW);
    }
  }
}

void turnLights(){
  turnLightsBtnState.changeState(digitalRead(turnLightsBtnPin));
  if(!isInEmergencyMode){
    switch(turnLightsBtnState.btnCounterState){
      case 0:
        leftTurnSignal.startFlashing();
      break;
      case 1:
        leftTurnSignal.stopFlashing();
      break;
      case 2:
        rightTurnSignal.startFlashing();
      break;
      case 3:
        rightTurnSignal.stopFlashing();
      break;
      default:
        leftTurnSignal.stopFlashing();
        rightTurnSignal.stopFlashing();
      break;
    }
  }else{
    turnLightsBtnState.resetStateCounter();
  }
}

void emergencyLights(){
  emergencyLightsBtnState.changeState(digitalRead(emergencyLightsBtnPin));
  switch(emergencyLightsBtnState.btnCounterState){
    case 0:
      isInEmergencyMode = true;
      emergencyLeftSignal.startFlashing();
      emergencyRightSignal.startFlashing();
    break;
    case 1:
    default:
      if(isInEmergencyMode){
        isInEmergencyMode = false;
        emergencyLeftSignal.stopFlashing();
        emergencyRightSignal.stopFlashing();
      }
    break;
  }
}

void stopLights(){
  if(digitalRead(stopLightsBtnPin) == HIGH){
    digitalWrite(stopLightsPin, HIGH);
  }else{
    digitalWrite(stopLightsPin, LOW);
  }
}

