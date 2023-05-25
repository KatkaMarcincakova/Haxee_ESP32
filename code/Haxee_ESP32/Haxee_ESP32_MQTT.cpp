#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "Haxee_ESP32_MQTT.h"
#include "Haxee_ESP32_LEDStripe.h"

Haxee_ESP32_MQTT::Haxee_ESP32_MQTT(String ssid, String password, String mqtt_server, int mqtt_port, String t_sub, String t_pub) {
    ssid.toCharArray(_ssid, (ssid.length() + 1));
    password.toCharArray(_password, (password.length() + 1));
    mqtt_server.toCharArray(_mqtt_server, (mqtt_server.length() + 1));
    _mqtt_port = mqtt_port;
    _topic_sub = t_sub;
    _topic_pub = t_pub;
}

Haxee_ESP32_MQTT::Haxee_ESP32_MQTT() {}

WiFiClient espClient;
PubSubClient client(espClient);

bool Haxee_ESP32_MQTT::setup_wifi() {
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

bool Haxee_ESP32_MQTT::setup() {
    if (!setup_wifi()) {
        Serial.println("wifi setup FAIL");
        return false;
    }
    Serial.println("wifi setup OK");

    client.setServer(_mqtt_server, _mqtt_port);
    client.setCallback(callback);

    return true;
}

void Haxee_ESP32_MQTT::publish(String topic, String text) {
    String topic_pub = topic;
    if (topic.length() < 1)
        topic_pub = _topic_pub;

    char t[100];
    topic_pub.toCharArray(t, (topic_pub.length()+1));
    char tx[100];
    text.toCharArray(tx, (text.length()+1));
    client.publish(t, tx);
}

void Haxee_ESP32_MQTT::callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;
    
    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    if (String(topic) == "2023/start/checkResult") {
      Haxee_ESP32_LEDStripe ledstripe;
        if(messageTemp == "0"){
            ledstripe.lightError();
            delay(1500);
        }
        else if(messageTemp == "1"){
            ledstripe.lightSuccess();
            delay(1500);
        } else {
            ledstripe.lightInfo();
        }
    }
}

void Haxee_ESP32_MQTT::connect() {
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

bool Haxee_ESP32_MQTT::clientConnected() {
    return client.connected();
}

void Haxee_ESP32_MQTT::clientLoop() {
    client.loop();
}
