#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <KiTECH_LEDStripe.h>
#include <KiTECH_RC522.h>
#include "Haxee_ESP32.h"
#include "Haxee_ESP32_LEDStripe.h"

Haxee_ESP32::Haxee_ESP32(String ssid, String password, String mqtt_server, int mqtt_port, String t) {
    ssid.toCharArray(_ssid, (ssid.length() + 1));
    password.toCharArray(_password, (password.length() + 1));
    mqtt_server.toCharArray(_mqtt_server, (mqtt_server.length() + 1));
    _mqtt_port = mqtt_port;
    topic = t;
}

Haxee_ESP32::Haxee_ESP32() {}

Haxee_ESP32_LEDStripe ledstripe;
KiTECH_RC522 reader;
WiFiClient espClient;
PubSubClient client(espClient);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void Haxee_ESP32::error() {
  delay(500);
  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);
}

bool Haxee_ESP32::setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");

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
    pinMode(2, OUTPUT);

    if (!ledstripe.setup()) {
        return false;
    }
    
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
    timeClient.begin();
    timeClient.setTimeOffset(3600);

    return true;
}

void Haxee_ESP32::setupMessageColor(MessageType type, int r, int g, int b) {
    switch (type) {
        case Error:
            ledstripe.setError(r, b, g);
            break;
        case Info:
            ledstripe.setInfo(r, b, g);
            break;
        case Success:
            ledstripe.setSuccess(r, b, g);
            break;
        default:
            break;
    }
}

void Haxee_ESP32::lightLed(MessageType type) {
    if (type == Error) {
        ledstripe.lightError();
    } else if (type == Success) {
        ledstripe.lightSuccess();
    } else {
        ledstripe.lightInfo();
    }
}

String Haxee_ESP32::readCard() {
    if (reader.isNewCardPresent() && reader.readCardSerial()) {
        return reader.readCurrentCard();
    }
    
    return "Waiting for card";
}

void Haxee_ESP32::callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;
    
    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    if (String(topic) == "start/checkResult") {
      Haxee_ESP32 h;
        if(messageTemp == "0"){
            h.lightLed(Error);
            delay(1500);
        }
        else if(messageTemp == "1"){
            h.lightLed(Success);
            delay(1500);
        } else {
            h.lightLed(Info);
        }
    }
}

void Haxee_ESP32::reconnect() {
    unsigned long prev_millis = 0;

    while (!client.connected()) {
      digitalWrite(2,HIGH);
      if ((millis() - prev_millis > 5000)) {
          prev_millis - millis();
          Serial.print("Attempting MQTT connection ");
          Serial.print(_mqtt_server);
          Serial.print(" ");
          Serial.print(_mqtt_port);
          Serial.print(" ...");
          
          if (client.connect("ESP32Client")) {
            Serial.println("connected");
            
            client.subscribe("start/checkResult");
          } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
          }
      }
    }
    digitalWrite(2,LOW);
}

bool Haxee_ESP32::clientConnected() {
    return client.connected();
}

void Haxee_ESP32::clientLoop() {
    client.loop();
}

void Haxee_ESP32::timeLoop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
}

String Haxee_ESP32::formatMessage(String cardID) {
  String message = cardID;
  message.concat("|");
  message.concat(timeClient.getFormattedDate());
  return message;
}

void Haxee_ESP32::publish(String topic, String text) {
    char t[100];
    topic.toCharArray(t, (topic.length()+1));
    char tx[100];
    text.toCharArray(tx, (text.length()+1));
    client.publish(t, tx);
}
