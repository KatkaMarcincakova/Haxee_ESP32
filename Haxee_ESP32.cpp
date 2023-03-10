#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <KiTECH_LEDStripe.h>
#include <KiTECH_OLED_S.h>
#include <KiTECH_RC522.h>
#include "Haxee_ESP32.h"


Haxee_ESP32::Haxee_ESP32(String ssid, String password, String mqtt_server, int mqtt_port) {
    ssid.toCharArray(_ssid, ssid.length());
    password.toCharArray(_password, password.length());
    mqtt_server.toCharArray(_mqtt_server, mqtt_server.length());
    _mqtt_port = mqtt_port;
}

//Haxee_ESP32::~Haxee_ESP32(){}

KiTECH_LEDStripe ledstripe;
KiTECH_RC522 reader;
WiFiClient espClient;
PubSubClient client(espClient);

bool Haxee_ESP32::setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(_ssid);

    WiFi.begin(_ssid, _password);

    int limit = 0;

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (limit > 20) {
            return false;
        }
        limit++;
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    return true;
}

bool Haxee_ESP32::setup() {
    if (!ledstripe.setup()) {
        Serial.println("ledstripe setup FAIL");
        return false;
    }
    Serial.println("ledstripe setup OK");
    
    if (!reader.setup()) {
        Serial.println("reader setup FAIL");
        return false;
    }
    Serial.println("reader setup OK");

    if (!setup_wifi()) {
        Serial.println("wifi setup FAIL");
        return false;
    }
    Serial.println("wifi setup OK");

    client.setServer(_mqtt_server, _mqtt_port);
    client.setCallback(callback);

    return true;
}

void Haxee_ESP32::setupMessageColor(MessageType type, int r, int g, int b) {
    switch (type) {
        case Error:
            _errorR = r;
            _errorG = g;
            _errorB = b;
            break;
        case Info:
            _infoR = r;
            _infoG = g;
            _infoB = b;
            break;
        case Success:
            _successR = r;
            _successG = g;
            _successB = b;
            break;
        default:
            break;
    }
}

void Haxee_ESP32::ledError() {
    ledstripe.show_color(_errorR, _errorG, _errorB);
}

void Haxee_ESP32::ledInfo() {
    ledstripe.show_color(_infoR, _infoG, _infoB);
}

void Haxee_ESP32::ledSuccess() {
    ledstripe.show_color(_successR, _successG, _successB);
}

String Haxee_ESP32::readCard() {
    if (reader.isNewCardPresent() && reader.readCardSerial()) {
        return reader.readCurrentCard();
    }
    
    return "Waiting for card";
}

void Haxee_ESP32::callback(char* topic, byte* message, unsigned int length) {

}

void Haxee_ESP32::publish(String topic, String text) {

}
