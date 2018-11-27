// Including all the necessary headers

// Headers for all the libraries implemented
#include "Bounce2.h"          //debouncing the switches
#include <SPI.h>              // spi protocol 
#include <Adafruit_GFX.h>     // OLED graphics library
#include <Adafruit_SSD1325.h> // OLED driver library
#include <TMC2130Stepper.h> //Including TMC2130 Motor Driver Library

/*
   Including all the helper files created
*/

// Including the variables and constats setup page
#include "settings.h"

// Including the pins layout
#include "pcb_pins.h"

//Include the initialised vars
#include "init.h"

// Including the functions
#include "functions.h"
