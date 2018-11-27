/*
   ___ ____  ____       _    _____ __  __ ____  ____
  |_ _|  _ \/ ___|     / \  |  ___|  \/  |  _ \|  _ \
   | || |_) \___ \    / _ \ | |_  | |\/| | |_) | | | |
   | ||  _ < ___) |  / ___ \|  _| | |  | |  __/| |_| |
  |___|_| \_\____/  /_/   \_\_|   |_|  |_|_|   |____/

  AFMPD Calibration Rev1.0
  This code programs the teensy to do calibration of
  AFMPD in tank 8 of IRS Space Propulsion Lab

  Created 24th August 2018
  By Akash Mankar
*/

/*
    Dont hardcode the parameters in any of the files
    Settings.h have all the relevent settings which can
    can be changed, instructions are in comments there.
*/

// Including all the headers required for the program
#include "headers.h"

void setup() {
  // Setting ADC Resolution Read more :
  // https://www.arduino.cc/reference/en/language/functions/zero-due-mkr-family/analogreadresolution/
  //analogReadResolution(12);

  pinMode(obLED, OUTPUT);
  pinMode(switch1led, OUTPUT);
  pinMode(switch1p, INPUT);



  // Setting the limit switches with an internal pull-up
  pinMode(rsmot1, INPUT_PULLUP);
  pinMode(lsmot1, INPUT_PULLUP);
  pinMode(rsmot2, INPUT_PULLUP);
  pinMode(lsmot2, INPUT_PULLUP);
  pinMode(rsmot3, INPUT_PULLUP);
  pinMode(lsmot3, INPUT_PULLUP);

  //Setting RMS Current Values on motors
  sSM1.rms_current(900); // Set stepper current to 900mA
  sSM2.rms_current(1000); // Set stepper current to 1000mA
  sSM3.rms_current(600); // Set stepper current to 600mA

  //Turning on StealthChop for motors
  sSM1.stealthChop(1); // Enable extremely quiet stepping
  sSM2.stealthChop(1);
  sSM3.stealthChop(1);

  //Setting Microstepping Settings
  sSM1.microsteps(SM1ustep); // maybe overriden by PID
  sSM2.microsteps(SM2ustep);
  sSM3.microsteps(SM3ustep); // maybe overriden by PID

  //oled_boot();
  oled_boot();

  //Homing all the stages to known refernce point
  //  SM1home();
  //  SM2home();
  //  SM3home();

}

void loop() {
  updatedbswitches(); // limit switches status update


  for (int i = 0; i < 50; i++) {


    String myString = "Count => ";
    myString += i;

    oledtext(myString, 1);

  }
}
