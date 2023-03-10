#ifndef Haxee_ESP32_h
#define Haxee_ESP32_h

#include "Arduino.h"

class Haxee_ESP32
{
private:
    int _successR = 0;
    int _successG = 255;
    int _successB = 0;

    int _infoR = 0;
    int _infoG = 0;
    int _infoB = 255;

    int _errorR = 255;
    int _errorG = 0;
    int _errorB = 0;

    
    char _ssid[100];
    char _password[100];
    char _mqtt_server[100];
    int _mqtt_port = 1883;

    bool setup_wifi();
    void reconnect();

public:
    Haxee_ESP32(String ssid, String password, String mqtt_server, int mqtt_port);
    //Haxee_ESP32();

    enum MessageType { Error, Success, Info };
    
    bool setup();
    String readCard();

    void setupMessageColor(MessageType type, int r, int g, int b);
    void ledError();
    void ledSuccess();
    void ledInfo();

    void publish(String topic, String text);
    static void callback(char* topic, byte* message, unsigned int length);
};

#endif
