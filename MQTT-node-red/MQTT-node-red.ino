#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_BMP085.h>
#include "Adafruit_SHT31.h"

#define TimeSleep 600
//=====================================================================================================
//Thư viện và khai báo cho cảm biến
BH1750 lighter;
Adafruit_BMP085 bmp;
Adafruit_SHT31 sht31 = Adafruit_SHT31();

//Thiết lập cho mạng wifi và IP host cảu mqtt thích hợp
//Note(1-7-2017) dual wifi, setting dưới đây sẽ không đổi
const char* ssid = "Pi_ma_minh";
const char* password = "Raspberry";
const char* mqtt_server = "192.168.42.1";

WiFiClient espClient;
PubSubClient client(espClient);

//=======================================================================================================
void setup() {
  
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  Serial.println("Running..."); 
  
  lighter.begin();  
  bmp.begin();  
  sht31.begin(0x44);
   
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  while(!client.connected()){
    reconnect();  
  }
  char Temp[100]; char Hum [100]; char Light[100]; char Press[100];
  dtostrf(sht31.readTemperature(),10,2,Temp);
  dtostrf(sht31.readHumidity(),10,2,Hum);
  dtostrf(lighter.readLightLevel(),10,2,Light);
  dtostrf(bmp.readPressure(),10,2,Press);
  Serial.println("All message published !");
  client.publish("TopTemp",Temp);
  client.publish("TopHum",Hum);
  client.publish("TopLight",Light);
  client.publish("TopPress",Press);
  Serial.println("Sleeping..");
  ESP.deepSleep(TimeSleep*1000000,WAKE_RF_DEFAULT);
}

void loop() {
// Do nothing here
}

//***
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();Serial.print("Connecting to ");Serial.println(ssid); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  { delay(500); Serial.print(".");   } 
  Serial.println("");             
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}
//***
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.publish("outTopic", "hello world"); // Once connected, publish an announcement...
      client.subscribe("inTopic");               // ... and resubscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
