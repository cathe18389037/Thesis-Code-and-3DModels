#ifndef LCD_H
#define LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C getLcd();
void initLcd();
void updateLcd();

#ifdef	__cplusplus
}
#endif

#endif