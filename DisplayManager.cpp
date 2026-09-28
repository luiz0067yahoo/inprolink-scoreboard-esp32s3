#include "DisplayManager.h"

// 18 digits, 35 pixels each (5 LEDs per segment)
Adafruit_NeoPixel* digits[18] = {nullptr};
const int digitPins[18] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

// Segment map for digits 0-9 and Hex A-F (active high segment order: A, B, C, D, E, F, G)
const byte segmentMap[16] = {
  0b00111111, // 0: A, B, C, D, E, F
  0b00000110, // 1: B, C
  0b01011011, // 2: A, B, D, E, G
  0b01001111, // 3: A, B, C, D, G
  0b01100110, // 4: B, C, F, G
  0b01101101, // 5: A, C, D, F, G
  0b01111101, // 6: A, C, D, E, F, G
  0b00000111, // 7: A, B, C
  0b01111111, // 8: A, B, C, D, E, F, G
  0b01101111, // 9: A, B, C, D, F, G
  0b01110111, // A: A, B, C, E, F, G
  0b01111100, // b: C, D, E, F, G
  0b00111001, // C: A, D, E, F
  0b01011110, // d: B, C, D, E, G
  0b01111001, // E: A, D, E, F, G
  0b01110001  // F: A, E, F, G
};

uint32_t getDigitColor(int index) {
  // 0, 1, 2: Points A (Red)
  // 3, 4, 5: Points B (Red)
  // 6, 7: Fouls A (Orange)
  // 8, 9: Period (Yellow)
  // 10, 11: Fouls B (Orange)
  // 12-17: Timer (Green)
  if (index >= 0 && index <= 5) return 0xFF0000;
  if (index >= 6 && index <= 7) return 0xFF5500;
  if (index >= 8 && index <= 9) return 0xFFFF00;
  if (index >= 10 && index <= 11) return 0xFF5500;
  return 0x00FF00;
}

void drawDigit(int digitIndex, int val, uint32_t color) {
  if (digitIndex < 0 || digitIndex >= 18 || digits[digitIndex] == nullptr) return;
  Adafruit_NeoPixel* strip = digits[digitIndex];
  strip->clear();
  
  if (val >= 0 && val < 16) {
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
  // Scores Time A (3 digits: Centena, Dezena, Unidade)
  drawDigit(0, scoreA / 100, getDigitColor(0));
  drawDigit(1, (scoreA / 10) % 10, getDigitColor(1));
  drawDigit(2, scoreA % 10, getDigitColor(2));
  
  // Scores Time B (3 digits: Centena, Dezena, Unidade)
  drawDigit(3, scoreB / 100, getDigitColor(3));
  drawDigit(4, (scoreB / 10) % 10, getDigitColor(4));
  drawDigit(5, scoreB % 10, getDigitColor(5));
  
  // Fouls Time A (2 digits)
  drawDigit(6, foulsA / 10, getDigitColor(6));
  drawDigit(7, foulsA % 10, getDigitColor(7));

  // Period (2 digits)
  drawDigit(8, period / 10, getDigitColor(8));
  drawDigit(9, period % 10, getDigitColor(9));

  // Fouls Time B (2 digits)
  drawDigit(10, foulsB / 10, getDigitColor(10));
  drawDigit(11, foulsB % 10, getDigitColor(11));
  
  // Timer HH:MM:SS (6 digits)
  int hrs = totalSeconds / 3600;
  int mins = (totalSeconds % 3600) / 60;
  int secs = totalSeconds % 60;
  
  drawDigit(12, hrs / 10, getDigitColor(12));
  drawDigit(13, hrs % 10, getDigitColor(13));
  drawDigit(14, mins / 10, getDigitColor(14));
  drawDigit(15, mins % 10, getDigitColor(15));
  drawDigit(16, secs / 10, getDigitColor(16));
  drawDigit(17, secs % 10, getDigitColor(17));
}
