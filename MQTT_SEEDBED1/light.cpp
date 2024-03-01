#include "Arduino.h"
#include "light.h"
#include "Wire.h"   //i2c driver
#include <Adafruit_Sensor.h>     // Include Adafruit Unified Sensor Driver
#include "Adafruit_TSL2591.h"    // Include Adafruit TSL2591 library

//===================================================================
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
static float lux;

//===================================================================
static void processLight(){
  uint32_t tsl2591_data = tsl.getFullLuminosity();   // Get CH0 & CH1 data from the sensor (two 16-bit registers)
  uint16_t ir, ir_visible;
  ir = tsl2591_data >> 16;              // extract infrared value
  ir_visible = tsl2591_data & 0xFFFF;   // extract visible + infrared value
  lux = tsl.calculateLux(ir_visible, ir);   // Calculate light lux value
}

//===================================================================
static void printLux(){
  // Print light lux on serial monitor
  Serial.print(F("Light Level = ")); Serial.print(lux, 6); Serial.println( "lux" );
}

//===================================================================
void initLight(){
  Wire.begin();

  if (tsl.begin()) {
    Serial.println(F("Found a TSL2591 sensor"));
  }else{
    Serial.println(F("Sensor Not Found ... check wiring!"));
    while (1);   // stay here!
  }
  // Configure the gain and integration time for the TSL2591
  tsl.setGain(TSL2591_GAIN_LOW);                 // Set sensor gain to 25x
  tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // Set sensor integration time to 300 ms
}

//===================================================================
void updateLight(){
  processLight();
  //printLux();
}

//===================================================================
float getLight(){ return lux;}
