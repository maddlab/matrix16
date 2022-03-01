// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.
// Link to library doc: https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "ListLib.h"
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 6
#define NUMPIXELS 256

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, 3,
                            NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

const uint16_t topLeft[] = {0x0000, 0x0000};
const uint16_t topRight[] = {0x000f, 0x0000};
const uint16_t bottomRight[] = {0x000f, 0x000f};
const uint16_t bottomLeft[] = {0x0000, 0x000f};

const uint16_t randomColor = random(2147483647);

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(randomColor);
}

int x    = matrix.width();
int pass = 0;
uint16_t randomCo = random(2147483647);

void loop() {

    rect_zoom_inOut(topLeft, randomCo, 55);
    rect_zoom_inOut(topLeft, randomCo, 55);
    draw_x(topLeft, 55);
    draw_x(topLeft, 55);
    //      random_for_now();
    
    matrix.show();
    delay(300);

  //int i = 4;

  for (int i = 0 ; i < 16; i++)
  {
    uint16_t randomCo = 0x7568C6;
    matrix.drawLine(topLeft[0], topLeft[1] + i, bottomRight[0], bottomRight[1] - i, randomCo);
    matrix.show();
    delay(55);
  }
  for (int i = 0 ; i < 16; i++)
  {
    uint16_t randomCo = 0xF63B4E;
    matrix.drawLine(topLeft[0] + i, topLeft[1], bottomRight[0] - i, bottomRight[1], randomCo);
    matrix.show();
    delay(55);
  }
  for (int i = 0 ; i < 16; i++)
  {
    uint16_t randomCo = 0x3BDFF6;
    matrix.drawLine(topLeft[0] , topLeft[1] - i, bottomRight[0], bottomRight[1] - i, randomCo);
    matrix.show();
    delay(55);
  }
  for (int i = 0 ; i < 16; i++)
  {
    uint16_t randomCo = 0x3BDFF6;
    matrix.drawLine(topLeft[0], topLeft[1] + i, bottomRight[0], bottomRight[1] + i, randomCo);
    matrix.show();
    delay(55);
  }

  matrix.clear();

  //  for (int i = 0 ; i < 16; i++)
  //  {
  //
  //    matrix.drawLine(topLeft[0]], topLeft[1], bottomRight[0]], bottomRight[1], randomCo);
  //    matrix.show();
  //    delay(150);
  //  }

}



/*Helper Functions*/



void random_for_now()
{
  matrix.clear();
  for (int i = 0; i < 700; i++)
  {
    int r1 = random(0, 16);
    int r2 = random(0, 16);
    matrix.drawPixel(r1, r2, randomCo);
    matrix.show();
    //delay(10);
  }
}

void draw_x(uint16_t origin[], int delayTime)
{
  uint16_t randomCo = random(2147483647);
  for (int i = 0; i < 16; i++)
  {
    uint16_t px = random(0, 15);
    matrix.drawPixel(topLeft[0] + i, topLeft[1] + i, randomCo);
    matrix.drawPixel(topRight[0] - i, topRight[1] + i, randomCo);
    matrix.show();
    delay(45);
  }
  matrix.clear();
}

void rect_zoom_inOut(uint16_t origin[], uint16_t color, int delayTime)
{
  zoom_out_rect(topLeft, color, 55);
  zoom_in_rect(topLeft, color, 55);
}

void zoom_out_rect(uint16_t origin[], uint16_t color, int delayTime)
{
  uint16_t randomColor = random(2147483647);
  matrix.drawRect(topLeft[0] + 7, topLeft[1] + 7, 2, 2, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);

  matrix.drawRect(topLeft[0] + 6, topLeft[1] + 6, 4, 4, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);

  matrix.drawRect(topLeft[0] + 5, topLeft[1] + 5, 6, 6, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);

  matrix.drawRect(topLeft[0] + 4, topLeft[1] + 4, 8, 8, randomColor);
  matrix.show();
  matrix.clear();

  delay(delayTime);
  matrix.drawRect(topLeft[0] + 3, topLeft[1] + 3, 10, 10, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);

  matrix.drawRect(topLeft[0] + 2, topLeft[1] + 2, 12, 12, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);

  matrix.drawRect(topLeft[0] + 1, topLeft[1] + 1, 14, 14, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);

  matrix.drawRect(topLeft[0], topLeft[1], 16, 16, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
}

void zoom_in_rect(uint16_t origin[], uint16_t color, int delayTime)
{
  uint16_t randomColor = random(2147483647);
  matrix.drawRect(topLeft[0], topLeft[1], 16, 16, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
  matrix.drawRect(topLeft[0] + 1, topLeft[1] + 1, 14, 14, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
  matrix.drawRect(topLeft[0] + 2, topLeft[1] + 2, 12, 12, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
  matrix.drawRect(topLeft[0] + 3, topLeft[1] + 3, 10, 10, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
  matrix.drawRect(topLeft[0] + 4, topLeft[1] + 4, 8, 8, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
  matrix.drawRect(topLeft[0] + 5, topLeft[1] + 5, 6, 6, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
  matrix.drawRect(topLeft[0] + 6, topLeft[1] + 6, 4, 4, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
  matrix.drawRect(topLeft[0] + 7, topLeft[1] + 7, 2, 2, randomColor);
  matrix.show();
  matrix.clear();
  delay(delayTime);
  matrix.clear();
}
