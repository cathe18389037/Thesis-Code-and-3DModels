#include "Arduino.h"
#include "uv.h"
#include "Wire.h"
#include "lcd.h"

#include <Adafruit_Sensor.h> 
#include <Adafruit_SI1145.h>
//===================================================================

Adafruit_SI1145 si1145 = Adafruit_SI1145();
static float uv, UVindex;

//===================================================================
static void processUv(){
  uv = si1145.readUV();
  UVindex = uv/100.0;  
}

//===================================================================
static void printUV(unsigned long interval){
  static unsigned long now, past=0;
  now= millis();
  if(now-past>interval){
    past= now;
    Serial.print("UV: ");  Serial.println(uv);
  }
}

//===================================================================
static void printUVIndex(unsigned long interval){
  static unsigned long now, past=0;
  now= millis();
  if(now-past>interval){
    past= now;
    Serial.print("UVIndex: ");  Serial.println(UVindex);
  }
}

//===================================================================
void initUv(){
  Wire.begin();
  if (si1145.begin()) {
    Serial.println("Adafruit SI1145 Ok");
  }else{
    Serial.println("Didn't find Si1145");
    while (1);
  }
}

//===================================================================
void updateUv(){
  processUv();
  //printUVIndex();
  //printUV();
}

//===================================================================
float getUv(){ return uv; }
float getUVIndex(){ return UVindex; }
