#ifndef LEDS_H
#define LEDS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LED1 BUILTIN_LED
#define LED2 26

void toggleLed1(unsigned long interval);
void toggleLed2(unsigned long interval);

void initLeds();
void updateLeds();

#ifdef	__cplusplus
}
#endif

#endif