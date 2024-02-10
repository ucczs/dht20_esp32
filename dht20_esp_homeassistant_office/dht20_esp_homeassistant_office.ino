#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DFRobot_DHT20.h>

#include <MQTT.h>
#include "credentials.h"
#include "settings.h"

#include <ArduinoOTA.h>

WiFiClient net;
MQTTClient mqtt;
DFRobot_DHT20 dht20;
int reset_counter = 0;

void setup() {

  delay(500);

  Serial.begin(115200);
  Serial.println();

  connect_wifi();

  Serial.println("Wifi connected...");

  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
  }
  Serial.println("DHT20 sensor connected");

  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.begin();
}

void connect_wifi() {
  WiFi.mode(WIFI_AP_STA);
  while(WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(500);
    Serial.println("WiFi connection failed. Retry.");
  }

  WiFi.hostname(hostname);
  Serial.print("Wifi connection established. IP-Address: ");
  Serial.println(WiFi.localIP());
}

void connect_mqtt() {
  mqtt.begin(host, net);
  while (!mqtt.connect(host, mqttuser, mqttpwd)) {
    Serial.print(".");
  }
  Serial.println("\nMQTT connected!\n");
  delay(500);
}

void loop(){
  connect_mqtt();
  mqtt.loop();

  float temperature = dht20.getTemperature();
  float humidity = dht20.getHumidity()*100;
  
  char temperature_char[5];
  char humidity_char[5];
  dtostrf(temperature, 4, 1, temperature_char);
  dtostrf(humidity, 4, 0, humidity_char);

  Serial.print("Sending...\n");
  Serial.print("Temp: ");
  Serial.print(temperature_char);
  Serial.print(" °C, ");
  Serial.print("Humidity: ");
  Serial.print(humidity_char);
  Serial.print(" %\n");
  mqtt.publish(topicNameTemp, temperature_char);
  mqtt.publish(topicNameHumidity, humidity_char);

  mqtt.disconnect();

  ArduinoOTA.handle();
  delay(30000);
  reset_counter++;

  if(reset_counter > 20)
  {
    reset_counter = 0;
    ESP.restart();
  }
}