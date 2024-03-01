#include "leds.h"
#include "temp.h"
#include "light.h"
#include "lcd.h"
#include "moisture.h"
#include "Secret.h"
#include <WiFi.h>
#include <PubSubClient.h>

//===================================================================
const char *ID   = "SeedBed_1";         // Name of our device, must be unique
const char *TOPIC_Light= "room/light";  // Topic to subcribe to
const char *TOPIC_TEMP = "room/temp";
const char *TOPIC_Moist= "room/moist"; 

const char* mqttServer = "192.168.1.200";  // Broker address

WiFiClient wclient;
PubSubClient client(wclient);
const int pumpPin = 14;

//===================================================================
static String get_wifi_status(int status){
  switch(status){
    case WL_IDLE_STATUS:        return "WL_IDLE_STATUS";
    case WL_SCAN_COMPLETED:     return "WL_SCAN_COMPLETED";
    case WL_NO_SSID_AVAIL:      return "WL_NO_SSID_AVAIL";
    case WL_CONNECT_FAILED:     return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST:    return "WL_CONNECTION_LOST";
    case WL_CONNECTED:          return "WL_CONNECTED";
    case WL_DISCONNECTED:       return "WL_DISCONNECTED";
  }
  return "UNKNOWN";
}

//===================================================================
// Connect to WiFi network
void setup_wifi() {
  int status = WL_IDLE_STATUS;
  Serial.print("\nConnecting to "); Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass); // Connect to network

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500); 
    status = WiFi.status();
    Serial.println(get_wifi_status(status));
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  getLcd().setCursor(0,0); getLcd().print(WiFi.localIP());
}

//===================================================================
// Reconnect client to server
//===================================================================
void reconnect() {
  while(!client.connected()){
    Serial.print("Attempting MQTT connection...");
    if(client.connect(ID)) {
      Serial.println("connected");
      client.subscribe("esp32/output");
    }else{
      Serial.println(" try again in 5 seconds"); delay(5000);
    }
  }
}

//===================================================================
// publish to Topics
//===================================================================
static void refreshValue(unsigned long interval){
  static unsigned long now, past;
  now= millis();
  if(now-past>interval){
    past= now;
    client.publish(TOPIC_Light, String(getLight()).c_str() );
    client.publish(TOPIC_TEMP,  String(getTemp()).c_str() );
    client.publish(TOPIC_Moist, String(getMoist()).c_str() );
   }
}

//===================================================================
// Process received messages
//===================================================================
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Arrived on topic: "); Serial.print(topic);  Serial.print(".Message: ");  
  String msg;
  
  for(int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    msg += (char)message[i];
  }
  Serial.println();

  if(String(topic) == "esp32/output") {
    Serial.print("pump: ");
    if(msg == "on"){
      Serial.println("on");   digitalWrite(pumpPin, LOW);
    }else if(msg == "off"){
      Serial.println("off");  digitalWrite(pumpPin, HIGH);
    }
  }
}

//===================================================================
void setup() {
  Serial.begin(115200);
  while(!Serial) { delay(10); }
  delay(1000);
  setup_wifi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
  pinMode(pumpPin, OUTPUT); digitalWrite(pumpPin, HIGH);

  initLeds();
  initLcd();
  initTemp();
  initLight();
  initMoisture();
}

//===================================================================
void loop() {
  if(!client.connected()){ reconnect(); }
  client.loop();
  refreshValue(5000);
  
  updateLeds();
  updateLcd();
  updateTemp();
  updateLight();
  updateMoisture();
}
