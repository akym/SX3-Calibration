// Definations of all the pins on PCB rev1.0
// refer schematics if change is needed

#define obLED 13 //onbloard LED - testing

/*
   OLED Pin Definations
*/

// These are neede for hardware SPI
#define OLED_CS 23   // chip select for OLED
#define OLED_RESET 21 // reset signal, hooked in spare SPI cs pin
// this shouldn't be the case,usually the SPI devices
// share reset, the used library implementation doesn't allow that
#define OLED_DC 22   // data/command pin for oled
// Refer more OLED pinout and instructions on -
// https://learn.adafruit.com/2-7-monochrome-128x64-oled-display-module?view=all


/*
   LED Switches Pin Definations
   Naming convention, as seen on panel
   Development mode
                          _________
   1   2   3 - Top        | OLED  |
   4   5   6 - Bottom     |_______|

  Deployed Status
   6   5   4- Top        | OLED  |
   3   2   1 - Bottom     |_______|

*/

#define switch6p 52         // switch 1 NC pin  //NC - Normal Closed
#define switch6led 36      // switch 1 led pin

#define switch5p 53         // switch 2 NC pin 
#define switch5led 35      // switch 2 led pin

#define switch4p 54         // switch 3 NC pin 
#define switch4led 34      // switch 3 led pin

#define switch3p 50         // switch 4 NC pin 
#define switch3led 39      // switch 4 led pin

#define switch2p 49         // switch 5 NC pin 
#define switch2led 38      // switch 5 led pin

#define switch1p 51         // switch 6 NC pin 
#define switch1led 37      // switch 6 led pin


/*
   Motor Controller Definations
*/
// Stepper Motors
// SM1 - Force Sensor Unit
// SM2 - Distance Sensor unit
// SM3 - Calibration Unit

//motor 3 - SM3
//callibration unit
#define stepmot3 42
#define dirmot3 41
#define enmot3 46
#define csmot3 43
#define mosimot3 45
#define sckmot3 44
#define lsmot3 4
#define rsmot3 3

//motor 2 - SM2
//distaance sensor
#define stepmot2 24
#define dirmot2 40
#define enmot2 28
#define csmot2 25
#define mosimot2 27
#define sckmot2 26
#define lsmot2 30  // limit switch away from thrust balance
#define rsmot2 29 // limit switch near thrust balance

//motor 1 - SM1
// (force sensor translation stage)
// operated in unipolar mode for faster speed
#define dirmot1 5
#define stepmot1 6
#define csmot1 7
#define sckmot1 8
#define mosimot1 9
#define enmot1 10
#define rsmot1 32
#define lsmot1 31

//pseudo-pins for motors, not used with software SPI
#define misomot1 47
#define misomot2 48
#define misomot3 18

/*
   PID Pins Definations
*/
#define forcesense A0 // Pin for force sensor input, internally on ADC0
#define distsense A14 // Pin for force sensor input, internally on ADC1

/*
   SPI Definations
*/
#define spi1cs 21 // spare SPI chip select pin for future upgrades
#define spi2cs 20 // spare SPI chip select pin for future upgrades

/*
   Misc Definations
*/
#define tx 48 //serial/UART Tx pin
#define rx 47 //serial/UART Rx pin
#define sdaiic 18 //I2C SDA pin
#define scliic 19 //I2C SCL pin
