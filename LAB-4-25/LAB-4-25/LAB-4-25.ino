#include "LedController.hpp"

// LedControl lc = LedControl(18, 23, 5, 1); ยกเลิกใช้
#define DIN 23
#define CS 5
#define CLK 18
LedController<1, 1> lc;

void setup() {
  lc = LedController<1, 1>(DIN, CLK, CS);
  // lc.shutdown(0, false); ยกเลิกใช้
  // lc.setIntensity(0, 10); ยกเลิกใช้
  lc.setIntensity(2);
  // lc.clearDisplay(); ยกเลิกใช้
  lc.clearMatrix();
}

void loop() {

  // PGM01
  // lc.setRow(0, 7, B01001111);  //E
  // lc.setRow(0, 6, B01110110);  //n
  // lc.setDigit(0,3,2,false);
  // lc.setDigit(0,2,0,false);
  // lc.setDigit(0,1,2,false);
  // lc.setDigit(0,0,3,false);
  // while (1);
  // PGM02
  // byte x,y,z;
  // esfdsf
  // dsf
  // dsf
  // dsf
  // s
  // PGM03
  
}
