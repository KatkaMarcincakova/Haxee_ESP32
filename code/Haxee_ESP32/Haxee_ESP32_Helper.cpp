#include <NTPClient.h>
#include <WiFiUdp.h>
#include "Haxee_ESP32_Helper.h"

Haxee_ESP32_Helper::Haxee_ESP32_Helper() {}

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void Haxee_ESP32_Helper::error() {
  delay(500);
  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);
}

bool Haxee_ESP32_Helper::setup() {
    pinMode(2, OUTPUT);

    timeClient.begin();
    timeClient.setTimeOffset(3600);

    return true;
}

void Haxee_ESP32_Helper::timeLoop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
}

String Haxee_ESP32_Helper::formatMessage(String cardID) {
  String message = cardID;
  message.concat("|");
  message.concat(timeClient.getFormattedDate());
  return message;
}
