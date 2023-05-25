#include <KiTECH_RC522.h>
#include "Haxee_ESP32_MFRC522.h"

Haxee_ESP32_MFRC522::Haxee_ESP32_MFRC522() {}

KiTECH_RC522 reader;

bool Haxee_ESP32_MFRC522::setup() {
    if (!reader.setup()) {
        Serial.println("reader setup FAIL");
        return false;
    }
    Serial.println("reader setup OK");
    return true;
}

String Haxee_ESP32_MFRC522::readCard() {
    if (reader.isNewCardPresent() && reader.readCardSerial()) {
        return reader.readCurrentCard();
    }
    
    return "Waiting for card";
}