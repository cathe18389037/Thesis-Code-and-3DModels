#include "Arduino.h"
#include "moisture.h"

const int moisturePin = A0;    //Pin 36
static int moisturePercentage; //moisture reading

//===================================================================
static void processMoisture(){
  moisturePercentage = 100-((analogRead(moisturePin) / 4095.00) * 100.00 );
}

//===================================================================
static void printMoisture(unsigned long interval){
  static unsigned long now, past=0;
  now= millis();
  if(now-past>interval){
    past= now;
    Serial.print(moisturePercentage);  Serial.println("%");
   }
}

//===================================================================
void initMoisture(){
  
}

//===================================================================
void updateMoisture(){
  processMoisture();
  //printMoisture(3000);
}

//===================================================================
int getMoist(){ return moisturePercentage; }
