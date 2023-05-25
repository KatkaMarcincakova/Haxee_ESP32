#include "Haxee_ESP32.h"

void setup() {
	Haxee_ESP32 device("dominion2.4", "bobalk21a", "192.168.0.244", 1883, "2023/start/cardID");
    Serial.begin(9600);
    if (device.setup()) {
  		Serial.println("setup OK");
  		for (;;) {
  			cardReader(device);
  		}
    } else {
  		for (;;) {
        device.error();
      }
      	Serial.println("setup FAIL");  
    }
}

void cardReader(Haxee_ESP32 device) {
	device.timeLoop();
	if (!device.clientConnected()) {
		device.reconnect();
	}

	device.clientLoop();

	device.lightLed(device.Info);
	String card = device.readCard();
	Serial.println(card);
	
	if (card != "Waiting for card") {
		Serial.print("pub ");
		Serial.println(device.topic);
		device.publish(device.topic, device.formatMessage(card));
	} else {
		delay(500);
	}
}

void loop() {}
