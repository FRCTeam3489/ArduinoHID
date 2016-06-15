// Program to send input from digital and analog inputs to the
// FRC Drive Station
//
// Based on:
// Joystick Library by Matthew Heironimus at https://github.com/MHeironimus/ArduinoJoystickLibrary
// Debounce Logic by David A. Mellis / Limor Fried / Mike Walters at http://www.arduino.cc/en/Tutorial/Debounce
//
// Team 3489
// 06-11-2016
//
//--------------------------------------------------------------------
// Make changes to pin numbers & read delays in setup method
// Make changes to translate analog reads to dashboard in loop method
//--------------------------------------------------------------------
#include <Joystick3.h>

// Pin number to Digtal Button Number
int firstButton;   //Pin number to start assiging digital buttons
int lastButton;  // Pin number to stop assiging digital buttons

// Analog input assignment
int firstAnalog;  
int lastAnalog;

//Debounce - handle noise from the button, only respond ever x millisenconds
int buttonState;            
int lastButtonState;
int lastButtonPressed;
long lastDebounceTime;
long debounceDelay;

void setup() {
  //Seup number of buttons all on first joystick
  firstButton = 0;   //Pin number to start assiging buttons
  lastButton = 13;  // Pin number to stop assiging buttons
  
  // Setup 3 joysticks
  Joystick[0].begin();  // Joystick 1 in Drive Station
  Joystick[1].begin();  // Joystick 2 in Drive Station
  Joystick[2].begin();  // Joystick 3 in Drive Station
  
  //For each button set the pin to input with built in pullup
  for(int thisButton = firstButton; thisButton < (lastButton + 1); thisButton++) {    
    pinMode(thisButton, INPUT_PULLUP);    
  }

  firstAnalog = lastButton + 1;
  lastAnalog = 19;
  //If pins not used as digital buttons then assign analog input
  
  //Setup Debounce for buttons
  lastDebounceTime = 0;
  lastButtonPressed = lastButton + 1;
  buttonState = HIGH; // Default button state - caution INPUT_PULLUP switches state from INPUT
  debounceDelay = 50; // millisecons to ignore same state on button reads
}

void loop() {
  
  
  // Run through digital pins - for each button
  // record the button state (pressed or released) - compare the state and the button number
  // if the state and the button are the same, and the delay has not passed then do nothing
  // for new states, buttons, or the delay has passed then update the FRC dashboard
  for(int thisButton = firstButton; thisButton < (lastButton + 1); thisButton++) {
    int readButtonState = digitalRead(thisButton);
    if ((readButtonState != lastButtonState) && (thisButton != lastButtonPressed)) {
      lastDebounceTime = millis();
    }
    
    if((thisButton != lastButtonPressed) || ((millis() - lastDebounceTime) > debounceDelay)) {
      if (readButtonState != buttonState) {
        buttonState = readButtonState;
      }  
      
      // Send the button press or release to FRC dashboard
      if (buttonState == LOW) {
        Joystick[0].pressButton(thisButton);
      } else {
        Joystick[0].releaseButton(thisButton);
      }
    }
    //Recorde the last button pressed for debounce
    lastButtonPressed = thisButton;
  }

  // Run through analog pins
  // record the analog value (-127 to +127) - convert the number to decimal for FRC drive station
  // Analog reads on arduino takes 0.0001 seconds (10,000 times per second)
  // unconnected Arduino analog pins can fluctuate based on a number of factors https://www.arduino.cc/en/Reference/AnalogRead
  // FRC drive station does not update this often. your physical controls may appear to have a delay
  for(int thisAnalog = firstAnalog; thisAnalog < (lastAnalog + 1); thisAnalog++) {
    long readAnalog = analogRead(thisAnalog);
    long FRCvalue = readAnalog / 127; 
    if(thisAnalog = 14) { Joystick[0].setXAxis(FRCvalue);} // First joystick X
    if(thisAnalog = 15) { Joystick[0].setYAxis(FRCvalue);} // First joystick Y
    if(thisAnalog = 16) { Joystick[1].setXAxis(FRCvalue);} // Second joystick X
    if(thisAnalog = 17) { Joystick[1].setYAxis(FRCvalue);} // Second joystick Y
    if(thisAnalog = 18) { Joystick[2].setXAxis(FRCvalue);} // Third joystick X
    if(thisAnalog = 19) { Joystick[3].setYAxis(FRCvalue);} // Third joystick Y
  }
  
}

