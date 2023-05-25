/*********************************************************************
 * @file  Haxee_ESP32_MQTT.h
 * 
 * @brief Knižnica na komunikáciu za pomoci protokolu MQTT
 *********************************************************************/
#ifndef Haxee_ESP32_MQTT_h
#define Haxee_ESP32_MQTT_h

#include "Arduino.h"

class Haxee_ESP32_MQTT
{
private:
    char _ssid[100];
    char _password[100];
    char _mqtt_server[100];
    int _mqtt_port = 1883;

    String _topic_sub = "sub";
    String _topic_pub = "pub";

    unsigned long prev_millis = 0;

    /**
    * @brief Pripojenie na internet
    *
    * Funkcia sa za pomoci získaného ssid a hesla pripojí do siete
    * 
    * @return vracia informáciu o tom, či pripojenie bolo úspešné alebo nie
    */
    bool setup_wifi();

public:
    /**
     * @brief Konštruktor triedy Haxee_ESP32_MQTT.
     * 
    * @param ssid ssid siete
    * @param password heslo do siete
    * @param mqtt_server IP adresa, na ktorej je spustený MQTT broker
    * @param mqtt_port port, na ktorom je spustený MQTT broker
    * @param t_sub téma, pod ktorou odoberá správy
    * @param t_pub téma pod ktorou publikuje správy
     */
    Haxee_ESP32_MQTT(String ssid, String password, String mqtt_server, int mqtt_port, String t_sub, String t_pub);
    Haxee_ESP32_MQTT();
    
    /**
    * @brief Pripojenie na internet a nastavenie pre komunikáciu s MQTT broker-om.
    *
    * @return vracia informáciu o tom, či pripojenie a nastavenie bolo úspešné alebo nie
    */
    bool setup();
    
    /**
    * @brief Odošle správu na MQTT broker.
    * 
    * Funkcia odošle zadanú správu na MQTT broker. V prípade, že téma na vstupe je null, odošle správu pod základnou témou - témou, ktorá bola zadaná konštruktorom.
    * 
    * @param topic téma, pod ktorou má odoslať správu
    * @param text správa, ktorú má odoslať
    */
    void publish(String topic, String text);
    
    /**
    * @brief Spracovanie prijatých správ.
    * 
    * Funkcia spracuváva správy prijaté od MQTT brokera pod predom zadanou témou
    * 
    * @param topic téma, pod ktorou správa prišla
    * @param message správa
    * @param length dĺžka správy
    */
    static void callback(char* topic, byte* message, unsigned int length);

    /**
    * @brief Pripojenie na MQTT broker.
    *
    * Funkcia sa pokúša pripojiť na MQTT broker a zadať témy, ktoré má zaujem odoberať. Na signalizáciu napájania sa rozsvieti modrá LED dióda na mikrokontroléri. Akonáhle pripojenie je úspešné, LED dióda zhasne.
    * 
    */
    void connect();

    /**
    * @brief Kontrola pripojenia na MQTT broker
    *
    * Funkcia overí, či nedošlo k prerušeniu komunikácie s MQTT broker-om
    * 
    * @return vracia informáciu o tom, či pripojenie je stále udržané
    */
    bool clientConnected();

    /**
    * @brief Udržiavanie komunikácie s MQTT broker-om
    */
    void clientLoop();
};

#endif
