/*********************************************************************
 * @file  Haxee_ESP32_Helper.h
 * 
 * @brief Knižnica s pomocnými funkciami
 *********************************************************************/
#ifndef Haxee_ESP32_Helper_h
#define Haxee_ESP32_Helper_h

#include "Arduino.h"

class Haxee_ESP32_Helper
{
private:

public:
    Haxee_ESP32_Helper();

    /**
    * @brief Úvodné nastavenie
    *
    * Funkcia nastaví pin 2 (pin integrovanej LED diódy) na OUTPUT a spustí sa klient pre získavanie času
    * 
    * @return vracia informáciu o tom, či pripojenie a nastavenie bolo úspešné alebo nie
    */
    bool setup();

    /**
    * @brief Naformátovanie správy
    * 
    * Funkcia vytvorí z parametrku cardID a aktuálneho času reťazec. cardID a aktuálny čas je rozdelené |.
    * 
    * @return výsledný reťazec vo formáte e2:1b:dd:2a|rrrr-mm-ddThh:mm:ssZ
    */
    String formatMessage(String cardID);

    /**
    * @brief Aktualizácia času
    * 
    */
    void timeLoop();

    /**
    * @brief Naznačenie problému blikaním LED diódy
    *
    * Funkcia rozbliká integrovanú LED diódu na doske.
    * 
    */
    void error();
};

#endif
