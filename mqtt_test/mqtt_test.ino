#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <MQTT.h>
#include "credentials.h"

WiFiClient net;
MQTTClient mqtt;

void setup() {

  delay(500);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting...");

  connect();
  
  Serial.println("Setup completed...");

  mqtt.loop();

  Serial.print("Sending data via mqtt to ensor/temperature_office");
  mqtt.publish("sensor/temperature_office", "999999");

  mqtt.disconnect();


  ESP.deepSleep(1800e6);
}

void connect() {
  WiFi.mode(WIFI_AP_STA);
  while(WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(500);
    Serial.println("WiFi connection failed. Retry.");
  }

  Serial.print("Wifi connection established. IP-Address: ");
  Serial.println(WiFi.localIP());

  mqtt.begin(host, net);
  while (!mqtt.connect(host, mqttuser, mqttpwd)) {
    Serial.print("*");
  }
  Serial.println("MQTT connected!");
  delay(500);
}

void loop(){
}