#include "DisplayManager.h"

// 18 digits, 35 pixels each (5 LEDs per segment)
Adafruit_NeoPixel* digits[18] = {nullptr};
const int digitPins[18] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

// Mapa de segmentos baseado no diagrama do hardware:
// Bit 0 (a): Superior Esquerdo (LEDs 0-4)
// Bit 1 (b): Topo (LEDs 5-9)
// Bit 2 (c): Superior Direito (LEDs 10-14)
// Bit 3 (d): Meio / Centro (LEDs 15-19)
// Bit 4 (e): Inferior Esquerdo (LEDs 20-24)
// Bit 5 (f): Base / Inferior (LEDs 25-29)
// Bit 6 (g): Inferior Direito (LEDs 30-34)
const byte segmentMap[16] = {
  0b01110111, // 0: a, b, c, e, f, g
  0b01000100, // 1: c, g
  0b00111110, // 2: b, c, d, e, f
  0b01101110, // 3: b, c, d, f, g
  0b01001101, // 4: a, c, d, g
  0b01101011, // 5: a, b, d, f, g
  0b01111011, // 6: a, b, d, e, f, g
  0b01000110, // 7: b, c, g
  0b01111111, // 8: a, b, c, d, e, f, g
  0b01101111, // 9: a, b, c, d, f, g
  0b01011111, // A: a, b, c, d, e, g
  0b01111001, // b: a, d, e, f, g
  0b00110011, // C: a, b, e, f
  0b01111100, // d: c, d, e, f, g
  0b00111011, // E: a, b, d, e, f
  0b00011011  // F: a, b, d, e
};

uint32_t getDigitColor(int index) {
  (void)index;
  // Todos os dígitos em cor branca (R: 255, G: 255, B: 255)
  return 0xFFFFFF;
}

// Cache to avoid bit-banging WS2812B strips when digit value/color hasn't changed
static int cachedDigitVal[18] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
static uint32_t cachedDigitColor[18] = {0};

void invalidateDisplayCache() {
  for (int i = 0; i < 18; i++) {
    cachedDigitVal[i] = -1;
    cachedDigitColor[i] = 0;
  }
}

void drawDigit(int digitIndex, int val, uint32_t color) {
  if (digitIndex < 0 || digitIndex >= 18 || digits[digitIndex] == nullptr) return;
  
  // Fast return if the displayed digit has not changed
  if (cachedDigitVal[digitIndex] == val && cachedDigitColor[digitIndex] == color) {
    return;
  }
  cachedDigitVal[digitIndex] = val;
  cachedDigitColor[digitIndex] = color;

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
