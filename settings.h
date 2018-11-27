//OLED Orientation
// options 0, 1, 2 or 3
int oledrot = 0; // for developement mode, power switch on left, oled on right
//int oledrot=2; // for deployed mode, oled on left , power switch on right

// Delay between Calibration masses
// Not accounting for the time required to move the motors
int cal_delay_sec = 20;
//DO NOT CHANGE NEXT LINE, it converts seconds to millis
int cal_delay_tmr = cal_delay_sec * 1000;

// Stepper Motors
// SM1 - Force Sensor Unit
// SM2 - Distance Sensor unit
// SM3 - Calibration Unit

//Stepper Motor Speed Settings
//SM1 - ST2818L1006-B     - Max speed - 4000 RPM -> 800000 PPS -> 1 pulse per 1 microseconds
//SM2 - ST2818S1006-B     - Max Speed - 4000 RPM -> 800000 PPS -> 1 pulse per 1 microseconds
//SM3 - QSH4218-35-10-027 - Max Speed - 5000 PPS -> 5000 PPS   -> 1 pulse per 200 microseconds

//******DO NOT CHANGE NUMBER OF STEPS OR MICROSTEPPING SETIING FOR ANY MOTOR, THIS WILL CAUSE MALFUNCTION********//

int sm1speeddelay = 1;  // in microsec -> results in one pulse twice this time
int sm2speeddelay = 200; // in microsec -> results in one pulse twice this time
int sm3speeddelay = 100; // in microsec -> results in one pulse twice this time

//Stepper Motor Microstepping Settings
int SM1ustep = 1;
int SM2ustep = 8;
int SM3ustep = 4;

//Calibration Motor steps
//manually counted
int rls2m1 = 0; //right/top limit switch to mass1 - 14-16 turns from rls
int m12m2 = 0; //mass 1 to mass 2 - 26-28 turns  - 26-28 turns from rls
int m22m3 = 0; //mass 2 to mass 3 - 38-40 turns  - 38-40 turns from rls

//Set pre-load force

int  preforce = 5; //in Newtons
