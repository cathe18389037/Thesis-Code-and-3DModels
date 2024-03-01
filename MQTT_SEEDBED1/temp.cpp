//#include "Arduino.h"
#include "temp.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "lcd.h"

//===================================================================
const int oneWireBus = 4;     
OneWire oneWire(oneWireBus);
DallasTemperature DS18B20(&oneWire);
static float tempC; 

//===================================================================
static void processTemp(){
  DS18B20.requestTemperatures();
  tempC = DS18B20.getTempCByIndex(0); 
}

//===================================================================
void displayTemp(unsigned long interval){
  static unsigned long now, past=0;
  now= millis();
  if(now-past>interval){
    past= now;
    getLcd().setCursor(0,0);  getLcd().print("Temp= "); getLcd().print(tempC);
  }
}

//===================================================================
void printTemp(unsigned long interval){
  static unsigned long now, past=0;
  now= millis();
  if(now-past>interval){
    past= now;
    Serial.print(tempC);  Serial.println("ºC");
  }
}
//===================================================================
void initTemp(){
  DS18B20.begin();
  DS18B20.requestTemperatures();
  tempC = DS18B20.getTempCByIndex(0); 
}

//===================================================================
void updateTemp(){
  processTemp();
  //printTemp(3000);
  displayTemp(3000);
}

//===================================================================
float getTemp(){ return tempC;}
