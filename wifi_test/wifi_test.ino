#include <ESP8266WiFi.h>
#include "credentials.h"

void setup() {
  Serial.begin(115200);
  Serial.println("ESP starts");

  WiFi.begin(ssid, password);

  Serial.print("Connecting...");

  while(WiFi.status()!=WL_CONNECTED){

    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected! IP-Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
}