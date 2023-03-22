#include "Haxee_ESP32.h"

Haxee_ESP32 device("dominion2.4", "bobalkY21a", "192.168.0.244", 1883, "start/cardID");

void setup() {
    Serial.begin(9600);
    if (device.setup()) {
      Serial.println("setup OK");
    } else {
      Serial.println("setup FAIL");  
    }

}

void loop() {
  if (!device.clientConnected()) {
    device.reconnect();
  }

  device.clientLoop();

  device.lightLed(device.Info);
  String card = device.readCard();
  Serial.println(card);
  
  if (card != "Waiting for card") {
    Serial.print("pub ");
    Serial.println(device.topic);
    device.publish(device.topic, card);
  } else {
    delay(500);
  }
}
