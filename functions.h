// Stepper Motors
// SM1 - Force Sensor Unit
// SM2 - Distance Sensor unit
// SM3 - Calibration Unit

/*
   function to blink LED
   Input args - LED Pin and delay amount
*/
void stupblink(int LEDp, int dtimer) {
  digitalWrite(LEDp, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(dtimer);              // wait for a dtimer
  digitalWrite(LEDp, LOW);    // turn the LED off by making the voltage LOW
  delay(dtimer);              // wait for a dtimer
}

void clearoled() {
  // clears the OLED display
  // removes all content from OLED
  oled.clearDisplay();
}

void oled_boot() {
  /*
     OLED boot sequence, initialize the display and splash screen
  */
  oled.begin();
  oled.clearDisplay();
  // following line shows the splash screen
  oled.drawBitmap(0, 0, oled_splash_irs, 128, 64, 1);
  oled.display();
  delay(1000);
  clearoled();
  oled.setRotation(oledrot);
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.println("IRS AFMPD CALIBRAT- ION UNIT");
  oled.display();
  delay(1000);
  clearoled();
  oled.setCursor(10, 10);
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.println("Waiting for command");
  oled.display();
}

char * oledtext(String txt, int size) {
  oled.clearDisplay();
  oled.setRotation(oledrot);
  oled.setTextSize(size);
  oled.setTextColor(WHITE);
  oled.setCursor(5, 5);
  oled.println(txt);
  oled.display();
}

char * changetext(String str, int i, int j, int size) {
  oled.clearDisplay();
  oled.setRotation(oledrot);
  oled.setTextSize(size);
  oled.setTextColor(WHITE);
  oled.setCursor(i, j);
  oled.println(str);
  oled.display();
}

int ledState = LOW;
unsigned long previousMillis = 0;

void blinkmillis(int ledPin, long interval) {
  pinMode(ledPin, OUTPUT);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

}

void setgoup() {
  //sets direction of the calibration unit motor to go up
  //lifting the masses in horizontal cailb mode
  //dirmot1 refers to SM3, Calibration motor attached to SM3 on box, change if otherwise
  oledtext("Setting direction of Calibration to go up.", 1);
  digitalWrite(dirmot3, LOW);
}

void setgodown() {
  //sets direction of the calibration unit motor to go down
  //dropping the masses in horizontal cailb mode
  //dirmot1 refers to SM3, Calibration motor attached to SM3 on box, change if otherwise
  oledtext("Setting direction of Calibration to go down.", 1);
  digitalWrite(dirmot3, HIGH);
}

void setdistclose() {
  //sets direction of the distance sensor unit motor to go towards balance
  //closes the gap between thrust balance and sensor
  //dirmot2 refers to SM2, Distance sensor unit motor attached to SM2 on box, change if otherwise
  oledtext("Setting direction of Distance Sensor to go towards thrust balance.", 1);
  digitalWrite(dirmot2, HIGH);
}

void setdistaway() {
  //sets direction of the calibration unit motor to go away from balance
  //increases the distance between thrust balance and distance sensor
  //dirmot2 refers to SM2, Distance sensor unit motor attached to SM2 on box, change if otherwise
  oledtext("Setting direction of Distance Sensor to go away from thrust balance.", 1);
  digitalWrite(dirmot2, HIGH);
}


void updatedbswitches() {
  //Update debounced switches
  calibupswitch.update();
  calibdownswitch.update();
  distcloseswitch.update();
  distfarswitch.update();
  fsfarswitch.update();
  fscloseswitch.update();
}

void SM1move(int dir, int step, int ustep) {

  digitalWrite(enmot1, LOW); // enabling motor driver
  digitalWrite(dirmot1, dir); //setting direction to move
  // FOR SM1 LOW=>Towards Balance & HIGH=>Away from Balance
  sSM1.microsteps(ustep);    // setting the microstepps
  for (int i = 0; i < step; i++) {
    digitalWrite(step, HIGH);
    delayMicroseconds(sm1speeddelay);
    digitalWrite(step, LOW);
    delayMicroseconds(sm1speeddelay);
  }
  bool sm1homed = false;
}

bool homesense(Bounce db) {
  // Senses the limit switch press and returns false
  if (db.rose()) {
    return false;
  } else {
    return true;
  }
}



void SM1home() {
  if (!sm1homed) {
    oledtext("Homing Force Sensor Unit..", 1);
    digitalWrite(enmot1, LOW); // enabling motor driver
    digitalWrite(dirmot1, HIGH); //setting direction to move

    do {
      fsfarswitch.update();
      digitalWrite(stepmot1, HIGH);
      delayMicroseconds(sm1speeddelay);
      digitalWrite(stepmot1, LOW);
      delayMicroseconds(sm1speeddelay);
    } while (homesense(fsfarswitch));

    //move preset number of steps in other
    //direction to have a homing reference
    digitalWrite(dirmot1, LOW);
    for (int i = 0; i < 11; i++) {
      digitalWrite(stepmot1, HIGH);
      delayMicroseconds(sm1speeddelay);
      digitalWrite(stepmot1, LOW);
      delayMicroseconds(sm1speeddelay);
    }
    sm1homed = true;
    oledtext("Homing Force Sensor Unit..Done.", 1);
  }
  else {
    oledtext("Force Sensor Unit already at reference home.", 1);
  }

}

void SM2home() {
  if (!sm2homed) {
    oledtext("Homing Distance Sensor Unit..", 1);
    digitalWrite(enmot2, LOW); // enabling motor driver
    digitalWrite(dirmot2, HIGH); //setting direction to move
    do {
      distfarswitch.update();
      digitalWrite(stepmot2, HIGH);
      delayMicroseconds(sm2speeddelay);
      digitalWrite(stepmot2, LOW);
      delayMicroseconds(sm2speeddelay);
    } while (homesense(distfarswitch));

    //move preset number of steps in other
    //direction to have a homing reference
    digitalWrite(dirmot2, LOW);
    for (int i = 0; i < 11; i++) {
      digitalWrite(stepmot2, HIGH);
      delayMicroseconds(sm2speeddelay);
      digitalWrite(stepmot2, LOW);
      delayMicroseconds(sm2speeddelay);
    }
    sm2homed = true;
    oledtext("Homing Distance Sensor Unit..Done", 1);
  }
  else {
    oledtext("Distance Sensor Unit already at reference home.", 1);
  }
}

void SM3home() {
  if (!sm3homed) {
    oledtext("Homing Calibration Unit..", 1);
    digitalWrite(enmot3, LOW); // enabling motor driver
    digitalWrite(dirmot3, HIGH); //setting direction to move
    do {
      calibdownswitch.update();
      digitalWrite(stepmot3, HIGH);
      delayMicroseconds(sm3speeddelay);
      digitalWrite(stepmot3, LOW);
      delayMicroseconds(sm3speeddelay);
    } while (homesense(calibdownswitch));

    //move preset number of steps in other
    //direction to have a homing reference
    setgoup();

    for (int i = 0; i < 11; i++) {
      digitalWrite(stepmot3, HIGH);
      delayMicroseconds(sm3speeddelay);
      digitalWrite(stepmot3, LOW);
      delayMicroseconds(sm3speeddelay);
    }
    sm3homed = true;
    oledtext("Homing Calibration Unit..Done.", 1);
  }
  else {
    oledtext("Calibration Unit already at reference home.", 1);
  }
}

void decoupleTB() {
  oledtext("Decoupling thrust balance..", 1);
  //decouples the thrust balance
  //moves fixed number of steps
  //platform moves up
  setgoup();
  //VALUE OF i is determined manually by
  //analytical solution and visual inspcection
  for (int i = 0; i < 11; i++) {
    digitalWrite(stepmot3, HIGH);
    delayMicroseconds(sm3speeddelay);
    digitalWrite(stepmot3, LOW);
    delayMicroseconds(sm3speeddelay);
  }
  oledtext("Decoupling thrust balance..Done.", 1);
}

void lockTB() {
  oledtext("Locking thrust balance..", 1);
  //locks the thrust balance
  //moves towards the lower limit switch
  //platform moves down
  setgodown();

  //homes the motor, easiest way to lock the balance
  SM3home();

  oledtext("Thrust balance locked and motor at reference home.", 1);

}

void calibrateUp() {
  oledtext("Calibration Procedure - Up ....", 1);
  digitalWrite(enmot3, LOW); // enabling motor driver
  setgodown(); //setting direction to move down

  //moves fixed number of steps
  //platform moves up
  //VALUE OF i is determined manually by
  //analytical solution and visual inspcection
  for (int i = 0; i < 11; i++) {
    digitalWrite(stepmot3, HIGH);
    delayMicroseconds(sm3speeddelay);
    digitalWrite(stepmot3, LOW);
    delayMicroseconds(sm3speeddelay);
  }

  delay(cal_delay_tmr); //delaying for calib signal to acquire n stabilize

  //VALUE OF i is determined manually by
  //analytical solution and visual inspcection
  for (int i = 0; i < 11; i++) {
    digitalWrite(stepmot3, HIGH);
    delayMicroseconds(sm3speeddelay);
    digitalWrite(stepmot3, LOW);
    delayMicroseconds(sm3speeddelay);
  }

  delay(cal_delay_tmr); //delaying for calib signal to acquire n stabilize

  //VALUE OF i is determined manually by
  //analytical solution and visual inspcection
  for (int i = 0; i < 11; i++) {
    digitalWrite(stepmot3, HIGH);
    delayMicroseconds(sm3speeddelay);
    digitalWrite(stepmot3, LOW);
    delayMicroseconds(sm3speeddelay);
  }
  oledtext("Calibration Procedure - Up ....Done.", 1);
}

void calibrateDown() {
  oledtext("Calibration Procedure - Down .....", 1);
  digitalWrite(enmot3, LOW); // enabling motor driver
  setgoup() ;//setting motor direction to move up

  //moves fixed number of steps
  //platform moves up
  //VALUE OF i is determined manually by
  //analytical solution and visual inspcection
  for (int i = 0; i < 11; i++) {
    digitalWrite(stepmot3, HIGH);
    delayMicroseconds(sm3speeddelay);
    digitalWrite(stepmot3, LOW);
    delayMicroseconds(sm3speeddelay);
  }

  delay(cal_delay_tmr); //delaying for calib signal to acquire n stabilize

  //VALUE OF i is determined manually by
  //analytical solution and visual inspcection
  for (int i = 0; i < 11; i++) {
    digitalWrite(stepmot3, HIGH);
    delayMicroseconds(sm3speeddelay);
    digitalWrite(stepmot3, LOW);
    delayMicroseconds(sm3speeddelay);
  }

  delay(cal_delay_tmr); //delaying for calib signal to acquire n stabilize

  //VALUE OF i is determined manually by
  //analytical solution and visual inspcection
  for (int i = 0; i < 11; i++) {
    digitalWrite(stepmot3, HIGH);
    delayMicroseconds(sm3speeddelay);
    digitalWrite(stepmot3, LOW);
    delayMicroseconds(sm3speeddelay);
  }
  oledtext("Calibration Procedure - Down .....Done.", 1);
}

void PIDMoveFS() {
  oledtext("Fine PID Movement - Force Sensor", 1);
}

void PIDMoveDS() {
  oledtext("Fine PID Movement - Distance Sensor", 1);
}

void preLoad() {
  // Moves the platform towards thrust balance, pre-loads the force sensor
  oledtext("Preloading the force sensor..", 1);
  if (sm1homed) {
    float fgap = (currentForce - preforce)
    if (fgap > 10) {
      do{
      // course movement towards thrust balance
      oledtext("Preloading the force sensor..Course Movement", 1);
      SM1move(LOW, 10000, 1);
      }while();
    } else if (fgap < 10){
    //code here
    }
    //PID movement towards balance
    oledtext("Preloading the force sensor..Fine PID Movement", 1);
    PIDMoveFS();
    //
    oledtext("Preloading the force sensor..Done", 1);
  } else {
    oledtext("Please home the Force Sensor by pushing button #1.", 1);
  }
}
