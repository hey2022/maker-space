#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() { 
  Serial.begin(9600);
  u8g2.begin();
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
}

int distance_calc() {
  digitalWrite(3,LOW);
  delayMicroseconds(1);
  digitalWrite(3,HIGH);
  delayMicroseconds(10);
  digitalWrite(3,LOW);
  int distance = float (pulseIn(4,HIGH,18000)) / 58;
  return distance;
}

int check(int water_level) {
  if (distance_calc() < 45 && water_level > 0) {
    Serial.println("Water On");
    while (distance_calc() < 45 && water_level > 0) {
      --water_level;
      Serial.println(water_level);
      delay(50);
    }
    return water_level;
  } else if (distance_calc() > 45 && water_level < 100) {
    Serial.println("Toping up water");
    while (distance_calc() > 45 && water_level < 100) {
      ++water_level;
      Serial.println(water_level);
      delay(50);
    }
    return water_level;
  } else if (water_level == 0) {
    ++water_level;
    return water_level;
  }
}

void loop() {
  int water_level = 100;
  while (true) {
    water_level = check(water_level);
    char D[5] = {0};
    sprintf(D, "%d", distance_calc());
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, D);
    u8g2.sendBuffer(); 
  }
}
