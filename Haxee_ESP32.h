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

    
    String _ssid = "";
    String _password = "";
    String _mqtt_server = "";
    int _mqtt_port = 1883;

public:
    Haxee_ESP32(String ssid, String password, String mqtt_server, int mqtt_port);

    enum MessageType { Error, Success, Info };
    
    bool setup();
    String readCard();

    void setupMessageColor(MessageType type, int r, int g, int b);
    void ledError();
    void ledSuccess();
    void ledInfo();

    void reconnect();
    void callback();
    void publish(String topic, String text);
};

#endif
