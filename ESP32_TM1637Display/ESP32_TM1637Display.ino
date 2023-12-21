#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 19
#define DIO 18
TM1637Display display(CLK, DIO);
void setup() {
  display.setBrightness(0x0f);      //ปรับความสว่าง
}
void loop() {
  for(int i = 0 ; i <= 9999 ; i++){    //คำสั่ง for วนลูป 10000 รอบ
    display.showNumberDec(i, false);  //คำสั่งแสดงตัวเลขบนจอ 7-Segment
    // delay(10);
  }
}
