/*********************************************************************
 * @file  Haxee_ESP32_LEDStripe.h
 * 
 * @brief Knižnica na ovládanie LED pásika
 *********************************************************************/
#ifndef Haxee_ESP32_LEDStripe_h
#define Haxee_ESP32_LEDStripe_h

#include "Arduino.h"

class Haxee_ESP32_LEDStripe
{
private:
    int _success[3] = {0, 255, 0};

    int _info[3] = {0, 0, 255};

    int _error[3] = {255, 0, 0};

public:
    /**
     * @brief Konštruktor triedy Haxee_ESP32_LEDStripe.
     */
    Haxee_ESP32_LEDStripe();
    
    /**
    * @brief Nastavenie modulu LED pásika
    *
    * @return vracia informáciu o tom, či nastavenie bolo úspešné alebo nie
    */
    bool setup();
    
    /**
    * @brief Rozsvietenie LED pásika na farbu značiacu chybu
    * 
    * Funkcia rozsvieti LED pásik na farbu, ktorá bola nastavená ako chybová farba
    */
    void lightError();

    /**
    * @brief Rozsvietenie LED pásika na farbu značiacu úspešný úkon
    * 
    * Funkcia rozsvieti LED pásik na farbu, ktorá bola nastavená ako úspešná farba
    */
    void lightSuccess();

    /**
    * @brief Rozsvietenie LED pásika na základnú / informačnú farbu
    * 
    * Funkcia rozsvieti LED pásik na farbu, ktorá bola nastavená ako informačná farba
    */
    void lightInfo();

    /**
    * @brief Nastavenie farby pre chybu
    * 
    * Funkcia nastaví nový RGB kód pre chybovú farbu
    * 
    * @param r Prvá (RED) hodnota z RGB kódu
    * @param g Druhá (GREEN) hodnota z RGB kódu
    * @param b Tretia (BLUE) hodnota z RGB kódu
    */
    void setError(int r, int g, int b);

    /**
    * @brief Nastavenie farby pre úspešný úkon
    * 
    * Funkcia nastaví nový RGB kód pre úspešnú farbu
    * 
    * @param r Prvá (RED) hodnota z RGB kódu
    * @param g Druhá (GREEN) hodnota z RGB kódu
    * @param b Tretia (BLUE) hodnota z RGB kódu
    */
    void setSuccess(int r, int g, int b);

    /**
    * @brief Nastavenie informačnej farby
    * 
    * Funkcia nastaví nový RGB kód pre inoformačnú farbu
    * 
    * @param r Prvá (RED) hodnota z RGB kódu
    * @param g Druhá (GREEN) hodnota z RGB kódu
    * @param b Tretia (BLUE) hodnota z RGB kódu
    */
    void setInfo(int r, int g, int b);
};

#endif