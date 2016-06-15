// Program to send input from digital and analog inputs to the
// FRC Drive Station
//
// Based on Joystick Library by Matthew Heironimus
// https://github.com/MHeironimus/ArduinoJoystickLibrary
// 
// Team 3489
// 06-11-2016

//------------------------------------------------------------
#include <Joystick3.h>

void setup() {
  // put your setup code here, to run once:
    Joystick[0].begin();  // Joystick 1 in Drive Station
    Joystick[1].begin();  // Joystick 2 in Drive Station
    Joystick[2].begin();  // Joystick 3 in Drive Station

}

void loop() {
  // put your main code here, to run repeatedly:
    Joystick[0].setButton(0,1);  // Button 1 on Joystick 1 in Drive Station
    Joystick[1].setButton(1,1); // Button 2 on Joystick 2 in Drive Station
    Joystick[2].setButton(2,1); // Button 3 on Joystick 3 in Drive Station
}

