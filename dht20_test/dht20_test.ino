#include <DFRobot_DHT20.h>

DFRobot_DHT20 dht20;
void setup(){

  Serial.begin(115200);
  //Initialize sensor
  while(dht20.begin()){
    Serial.println("DHT20 initialization failed. Retry.");
    delay(1000);
  }
}

void loop(){
  Serial.print("temp:"); 
  Serial.print(dht20.getTemperature());
  Serial.print("°C");

  Serial.print("humidity:"); 
  Serial.print(dht20.getHumidity()*100);
  Serial.println(" %");
  
  delay(1000);

}
