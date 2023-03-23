#ifndef Haxee_ESP32_h
#define Haxee_ESP32_h

#include "Arduino.h"

class Haxee_ESP32
{
private:
    int _success[3] = {0, 255, 0};

    int _info[3] = {0, 0, 255};

    int _error[3] = {255, 0, 0};

    
    char _ssid[100];
    char _password[100];
    char _mqtt_server[100];
    int _mqtt_port = 1883;

    bool setup_wifi();

public:
    Haxee_ESP32(String ssid, String password, String mqtt_server, int mqtt_port, String t);
    Haxee_ESP32();

    enum MessageType { Error, Success, Info };
    
    String topic = "";

    bool setup();
    String readCard();
    String formatMessage(String cardID);

    void setupMessageColor(MessageType type, int r, int g, int b);

    void publish(String topic, String text);
    static void callback(char* topic, byte* message, unsigned int length);
    void reconnect();
    bool clientConnected();
    void clientLoop();
    void timeLoop();
    void lightLed(MessageType type);
};

#endif
