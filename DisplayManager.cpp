#include "DisplayManager.h"

// 16 digits, 35 pixels each (5 LEDs per segment)
Adafruit_NeoPixel* digits[16] = {nullptr};
const int digitPins[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

// Segment map for digits 0-9 (active high segment order: A, B, C, D, E, F, G)
const byte segmentMap[10] = {
  0b00111111, // 0: A, B, C, D, E, F
  0b00000110, // 1: B, C
  0b01011011, // 2: A, B, D, E, G
  0b01001111, // 3: A, B, C, D, G
  0b01100110, // 4: B, C, F, G
  0b01101101, // 5: A, C, D, F, G
  0b01111101, // 6: A, C, D, E, F, G
  0b00000111, // 7: A, B, C
  0b01111111, // 8: A, B, C, D, E, F, G
  0b01101111  // 9: A, B, C, D, F, G
};

uint32_t getDigitColor(int index) {
  // 0, 1: Points A (Red)
  // 2, 3: Points B (Red)
  // 4, 5: Fouls A (Orange)
  // 6, 7: Period (Yellow)
  // 8, 9: Fouls B (Orange)
  // 10-15: Timer (Green)
  if (index >= 0 && index <= 3) return 0xFF0000;
  if (index >= 4 && index <= 5) return 0xFF5500;
  if (index >= 6 && index <= 7) return 0xFFFF00;
  if (index >= 8 && index <= 9) return 0xFF5500;
  return 0x00FF00;
}

void drawDigit(int digitIndex, int val, uint32_t color) {
  if (digitIndex < 0 || digitIndex >= 16 || digits[digitIndex] == nullptr) return;
  Adafruit_NeoPixel* strip = digits[digitIndex];
  strip->clear();
  
  if (val >= 0 && val <= 9) {
    byte segments = segmentMap[val];
    for (int seg = 0; seg < 7; seg++) {
      bool lit = (segments >> seg) & 1;
      if (lit) {
        // segment has 5 LEDs
        for (int led = 0; led < 5; led++) {
          strip->setPixelColor(seg * 5 + led, color);
        }
      }
    }
  }
  strip->show();
}

void updatePhysicalDisplays() {
  // Scores
  drawDigit(0, scoreA / 10, getDigitColor(0));
  drawDigit(1, scoreA % 10, getDigitColor(1));
  drawDigit(2, scoreB / 10, getDigitColor(2));
  drawDigit(3, scoreB % 10, getDigitColor(3));
  
  // Fouls
  drawDigit(4, foulsA / 10, getDigitColor(4));
  drawDigit(5, foulsA % 10, getDigitColor(5));
  drawDigit(8, foulsB / 10, getDigitColor(8));
  drawDigit(9, foulsB % 10, getDigitColor(9));

  // Period
  drawDigit(6, period / 10, getDigitColor(6));
  drawDigit(7, period % 10, getDigitColor(7));
  
  // Timer HH:MM:SS
  int hrs = totalSeconds / 3600;
  int mins = (totalSeconds % 3600) / 60;
  int secs = totalSeconds % 60;
  
  drawDigit(10, hrs / 10, getDigitColor(10));
  drawDigit(11, hrs % 10, getDigitColor(11));
  drawDigit(12, mins / 10, getDigitColor(12));
  drawDigit(13, mins % 10, getDigitColor(13));
  drawDigit(14, secs / 10, getDigitColor(14));
  drawDigit(15, secs % 10, getDigitColor(15));
}
