/*********************************************************************
 * @file  Haxee_ESP32_MFRC522.h
 * 
 * @brief Knižnica na získavanie dát z čítačky kariet MFRC522
 *********************************************************************/
#ifndef Haxee_ESP32_MFRC522_h
#define Haxee_ESP32_MFRC522_h

#include "Arduino.h"

class Haxee_ESP32_MFRC522
{
private:

public:
    /**
     * @brief Konštruktor triedy Haxee_ESP32_MFRC522.
     */
    Haxee_ESP32_MFRC522();
    
    /**
    * @brief Nastavenie senzoru MFRC522.
    *
    * @return vracia informáciu o tom, či nastavenie bolo úspešné alebo nie
    */
    bool setup();

    /**
    * @brief Prečíta hodnotu z priloženej karty.
    *
    * @return vracia hodnotu prečítanú z priloženej karty ak načítanie bolo úspešné alebo "Waiting for card"
    */
    String readCard();
};

#endif