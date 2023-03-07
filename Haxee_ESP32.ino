#include "Haxee_ESP32.h"

Haxee_ESP32 device;

void setup() {
    Serial.begin(9600);
    if (device.setup()) {
      Serial.println("setup OK");
    } else {
      Serial.println("setup FAIL");  
    }
}

void loop() {
  Serial.println(device.readCard());
    //device.displayMessage(device.Info, device.readCard());
   // device.ledError();
   // delay(2000);
   // device.ledInfo();
    delay(2000);
    //device.ledSuccess();
   // delay(2000);
}
