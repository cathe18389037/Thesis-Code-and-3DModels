#include "Arduino.h"
#include "lcd.h"

#define LCD_ADDRESS 0x27
#define COLS 16
#define ROWS  2

LiquidCrystal_I2C lcd(LCD_ADDRESS, COLS, ROWS);

//===================================================================
LiquidCrystal_I2C getLcd(){
  return lcd;
}

//===================================================================
void initLcd(){
  lcd.init();
  lcd.backlight();
}

//===================================================================
void updateLcd(){
  
}