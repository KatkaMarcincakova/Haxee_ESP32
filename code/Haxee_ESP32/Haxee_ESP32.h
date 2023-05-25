#ifndef Haxee_ESP32_h
#define Haxee_ESP32_h

#include "Arduino.h"

class Haxee_ESP32
{
private:
    char _ssid[100];
    char _password[100];
    char _mqtt_server[100];
    int _mqtt_port = 1883;
    String _topic_sub = "";
    String _topic_pub = "";

public:
    Haxee_ESP32(String ssid, String password, String mqtt_server, int mqtt_port, String t_sub, String t_pub);
    Haxee_ESP32();

    enum MessageType { Error, Success, Info };
    

    bool setup();
    String formatMessage(String cardID);

    void setupMessageColor(MessageType type, int r, int g, int b);

    void lightLed(MessageType type);

    void error();
};

#endif
