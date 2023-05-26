#include "Haxee_ESP32_LEDStripe.h"
#include "Haxee_ESP32_MFRC522.h"
#include "Haxee_ESP32_MQTT.h"
#include "Haxee_ESP32_Helper.h"

void setup() {
	Haxee_ESP32_MQTT mqtt("dominion2.4", "bobalkY21a", "192.168.0.244", 1883, "2023/start/checkResult", "2023/start");
	Haxee_ESP32_LEDStripe ledstripe;
	Haxee_ESP32_MFRC522 reader;
	Haxee_ESP32_Helper helper;

    Serial.begin(9600);

    if (helper.setup() && mqtt.setup() && ledstripe.setup() && reader.setup()) {
  		Serial.println("setup OK");
  		for (;;) {
  			cardReader(mqtt, ledstripe, reader, helper);
  		}
    } else {
		Serial.println("setup FAIL");
		for (;;) {
        	helper.error();
		}  
    }
}

void cardReader(Haxee_ESP32_MQTT mqtt, Haxee_ESP32_LEDStripe ledstripe, Haxee_ESP32_MFRC522 reader, Haxee_ESP32_Helper helper) {
	helper.timeLoop();

	if (!mqtt.clientConnected()) {
		mqtt.connect();
	}

	mqtt.clientLoop();

	ledstripe.lightInfo();
	String card = reader.readCard();
	Serial.println(card);

	if (card != "Waiting for card") {
		Serial.print("pub ");
		mqtt.publish("", helper.formatMessage(card));
	} else {
		delay(500);
	}
}

void loop() {}
