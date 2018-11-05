#include "SoftwareSerial9.h"


#define TX_L 11
#define RX_L 10
#define TX_R 6
#define RX_R 5
#define LEDPIN 13

SoftwareSerial9 serial_left(RX_L,TX_L);
SoftwareSerial9 serial_right(RX_R,TX_R);

void setup() {
  serial_left.begin(26315);
  serial_right.begin(26315);
  Serial.begin(115200);
}

char c = ' ';
signed int sp_l=0;
signed int sp_r=0;

void loop() {
  Serial.println(c);
  if(c == ' ') {
    sp_l=0;
    sp_r=0;
  } else if(c == 'q') {
    sp_l -= 10;
  } else if(c == 'w') {
    sp_l += 10;
  } else if(c == '2') {
    sp_l += 100;
  }  else if(c == '1') {
    sp_l -= 100;
  } else if(c == 'o') {
    sp_r -= 10;
  } else if(c == 'p') {
    sp_r += 10;
  } else if(c == '0') {
    sp_r += 100;
  }  else if(c == '9') {
    sp_r -= 100;
  }
  Serial.print("speeds: ");
  Serial.print(sp_l);
  Serial.print(" / ");
  Serial.println(sp_r);
  do {
      serial_left.write9(256);
      serial_left.write9(sp_l & 0xFF);
      serial_left.write9((sp_l >> 8) & 0xFF);
      serial_left.write9(sp_l & 0xFF);
      serial_left.write9((sp_l >> 8) & 0xFF);
      serial_left.write9(85);
      
      serial_right.write9(256);
      serial_right.write9(sp_r & 0xFF);
      serial_right.write9((sp_r >> 8) & 0xFF);
      serial_right.write9(sp_r & 0xFF);
      serial_right.write9((sp_r >> 8) & 0xFF);
      serial_right.write9(85);
      delayMicroseconds(300);
  } while(!Serial.available());
  c=Serial.read();
}
