#include <KiTECH_LEDStripe.h>
#include "Haxee_ESP32_LEDStripe.h"

Haxee_ESP32_LEDStripe::Haxee_ESP32_LEDStripe() {}

KiTECH_LEDStripe ledstripe;

bool Haxee_ESP32_LEDStripe::setup() {
    if (!ledstripe.setup()) {
        Serial.println("ledstripe setup FAIL");
        return false;
    }
    Serial.println("ledstripe setup OK");
    return true;
}

void Haxee_ESP32_LEDStripe::lightError() {
    ledstripe.show_color(_error[0], _error[1], _error[2]);
}

void Haxee_ESP32_LEDStripe::lightSuccess() {
    ledstripe.show_color(_success[0], _success[1], _success[2]);
}

void Haxee_ESP32_LEDStripe::lightInfo() {
    ledstripe.show_color(_info[0], _info[1], _info[2]);
}

void Haxee_ESP32_LEDStripe::setError(int r, int g, int b) {
    _error[0] = r;
    _error[1] = g;
    _error[2] = b;
}

void Haxee_ESP32_LEDStripe::setSuccess(int r, int g, int b) {
    _success[0] = r;
    _success[1] = g;
    _success[2] = b;
}

void Haxee_ESP32_LEDStripe::setInfo(int r, int g, int b) {
    _info[0] = r;
    _info[1] = g;
    _info[2] = b;
}