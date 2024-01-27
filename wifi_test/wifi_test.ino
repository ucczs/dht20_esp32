#include <ESP8266WiFi.h>
#include "credentials.h"

void setup() {
  Serial.begin(115200); //Baudrate
  Serial.println("ESP starts");

  WiFi.begin(ssid, password);

  Serial.print("Connecting...");

  while(WiFi.status()!=WL_CONNECTED){ //Loop which makes a point every 500ms until the connection process has finished

    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected! IP-Address: ");
  Serial.println(WiFi.localIP()); //Displaying the IP Address

}

void loop() {
  // put your main code here, to run repeatedly:

}