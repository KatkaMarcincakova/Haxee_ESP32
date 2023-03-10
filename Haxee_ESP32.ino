#include "Haxee_ESP32.h"

Haxee_ESP32 device("dominion", "bobalkY21a", "192.168.0.244", 1883);

void setup() {
    Serial.begin(9600);
    if (device.setup()) {
      Serial.println("setup OK");
    } else {
      Serial.println("setup FAIL");  
    }
}

void loop() {
  device.ledInfo();
  
  String card = device.readCard();
  Serial.println(card);
  
  if (card != "Waiting for card") {
    if (card == " d3 e0 61 1a") {
      device.ledSuccess();
    } else {
      device.ledError();
    }
    delay(1500);
  } else {
    delay(500);
  }
}
