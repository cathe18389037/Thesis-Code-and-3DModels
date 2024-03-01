#include "Arduino.h"
#include "leds.h"

//===================================================================
void toggleLed1(unsigned long interval){
  static unsigned long now, past=0;
  static int state=0;
  now= millis();
  if(now-past>interval){
    past= now;
    state= !state;
    digitalWrite(LED1, state);
  }
}

//===================================================================
void toggleLed2(unsigned long interval){
  static unsigned long now, past=0;
  static int state=0;
  now= millis();
  if(now-past>interval){
    past= now;
    state= !state;
    digitalWrite(LED2, state);
  }
}

//===================================================================
void initLeds(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

//===================================================================
void updateLeds(){
  toggleLed1(500);
  toggleLed2(2000);
}