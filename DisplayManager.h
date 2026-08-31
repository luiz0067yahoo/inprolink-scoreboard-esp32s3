#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "Globals.h"

extern Adafruit_NeoPixel* digits[16];
extern const int digitPins[16];
extern const byte segmentMap[10];

uint32_t getDigitColor(int index);
void drawDigit(int digitIndex, int val, uint32_t color);
void updatePhysicalDisplays();

#endif // DISPLAY_MANAGER_H
