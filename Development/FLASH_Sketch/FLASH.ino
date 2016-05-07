class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long onTime;     // milliseconds of on-time
  long offTime;    // milliseconds of off-time
 
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated
 
  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);     
    
    onTime = on;
    offTime = off;
  
    ledState = LOW; 
    previousMillis = 0;
  }
 
  void startFlashing()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= onTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }

  void stopFlashing()
  {
    previousMillis = offTime;
    ledState = LOW;
    digitalWrite(ledPin, ledState);
  }
};

class BtnState
{
  public:
  bool isEnabled;
  bool isClicked;

  BtnState(){
    isEnabled = false;
    isClicked = false;
  }

  void changeState(int state){
    if(state == HIGH && !isEnabled){
      isEnabled = true;
      isClicked = !isClicked;
    }else if(state == LOW && isEnabled){
      isEnabled = false;
    }
  }
};

const int turnLightFlashDuration = 500;

const int shortLightPin = 13;
const int longLightPin = 12;
const int shortLightBtn = 9;
const int longLightBtn = 8;
const int leftTurnSignalBtn = 7;
const int rightTurnSignalBtn = 6;

BtnState shortLightsBtnState;
BtnState longLightsBtnState;
BtnState leftTurnSignalsBtnState;
BtnState rightTurnSignalsBtnState;

Flasher leftTurnSignal(11, turnLightFlashDuration, turnLightFlashDuration);
Flasher rightTurnSignal(10, turnLightFlashDuration, turnLightFlashDuration);

void setup() {
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  pinMode(shortLightPin, OUTPUT);
  pinMode(longLightPin, OUTPUT);
  
  pinMode(shortLightBtn, INPUT);
  pinMode(longLightBtn, INPUT);
  pinMode(leftTurnSignalBtn, INPUT);
  pinMode(rightTurnSignalBtn, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  shortLightsBtnState.changeState(digitalRead(shortLightBtn));
  if(shortLightsBtnState.isClicked){
    digitalWrite(shortLightPin, HIGH); 
  }else{
    digitalWrite(shortLightPin, LOW); 
  }

  longLightsBtnState.changeState(digitalRead(longLightBtn));
  if(longLightsBtnState.isClicked){
    digitalWrite(longLightPin, HIGH);
  }else{
    digitalWrite(longLightPin, LOW);
  }

  leftTurnSignalsBtnState.changeState(digitalRead(leftTurnSignalBtn));
  if(leftTurnSignalsBtnState.isClicked){
    leftTurnSignal.startFlashing();
  }else{
    leftTurnSignal.stopFlashing();
  }

  rightTurnSignalsBtnState.changeState(digitalRead(rightTurnSignalBtn));
  if(rightTurnSignalsBtnState.isClicked){
    rightTurnSignal.startFlashing();
  }else{
    rightTurnSignal.stopFlashing();
  }
}
