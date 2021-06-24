/*********************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x64 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define LED_Display Adafruit_SSD1306

#define OLED_RESET 4

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELAY 2
#define DISPLAY_H 128
#define DISPLAY_W 64

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000001, B10000000,
  B00000001, B10000000,
  B00000111, B11100000,
  B00000111, B11100000,
  B00000001, B10000000,
  B00000001, B10000000,
  B00111111, B11111100,
  B00111111, B11111100,
  B00000001, B10000000,
  B00000001, B10000000,
  B00000111, B10000000,
  B00000111, B11100000,
  B00000001, B11100000,
  B00000001, B10000000,
  B00000001, B10000000,
  B00000001, B10000000
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("ADAPTIVE ALARMS");

  LED_Display display0(OLED_RESET);
  LED_Display display1(OLED_RESET);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display0.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  // display0.display();
  // display1.display();
  // delay(2000);

  // Clear the buffer.
  display0.clearDisplay();
  display0.display();

  display1.clearDisplay();
  display1.display();

  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!

  // draw many lines
  //testdrawline(display0);
  // display0.display();

  display0.drawBitmap(0, 0,  logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH, WHITE);
  // display1.drawBitmap(100, 48,  logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH, WHITE);

  // testdrawbitmap(display0, display1, logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);

  display0.display();
  display1.display();
}


void loop() {

}


void testdrawbitmap(LED_Display display0, LED_Display display1, const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icon_pos0[NUMFLAKES][3];
  uint8_t icon_pos1[NUMFLAKES][3];

  // initialize
  for (uint8_t f = 0; f < NUMFLAKES; f++) {
    icon_pos0[f][XPOS] = random(DISPLAY_W);
    icon_pos0[f][YPOS] = 0;
    icon_pos0[f][DELAY] = random(5) + 1;
    Serial.print("x0: ");
    Serial.print(icon_pos0[f][XPOS], DEC);
    Serial.print(" y0: ");
    Serial.print(icon_pos0[f][YPOS], DEC);
    Serial.print(" dy0: ");
    Serial.println(icon_pos0[f][DELAY], DEC);
  }

  Serial.println("=============");

  for (uint8_t f = 0; f < NUMFLAKES; f++) {
    icon_pos1[f][XPOS] = random(DISPLAY_W);
    icon_pos1[f][YPOS] = 0;
    icon_pos1[f][DELAY] = random(5) + 1;
    Serial.print("x1: ");
    Serial.print(icon_pos1[f][XPOS], DEC);
    Serial.print(" y1: ");
    Serial.print(icon_pos1[f][YPOS], DEC);
    Serial.print(" dy1: ");
    Serial.println(icon_pos1[f][DELAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      Serial.print("Flake: ");
      Serial.println(f);

      Serial.println("0000------------");
      Serial.print("x0: ");
      Serial.print(icon_pos0[f][XPOS], DEC);
      Serial.print(" y0: ");
      Serial.print(icon_pos0[f][YPOS], DEC);
      Serial.print(" dy0: ");
      Serial.println(icon_pos0[f][DELAY], DEC);
      display0.drawBitmap(icon_pos0[f][XPOS], icon_pos0[f][YPOS], bitmap, w, h, WHITE);
      display0.display();
      
      Serial.println("1111------------");
      Serial.print("x1: ");
      Serial.print(icon_pos1[f][XPOS], DEC);
      Serial.print(" y1: ");
      Serial.print(icon_pos1[f][YPOS], DEC);
      Serial.print(" dy1: ");
      Serial.println(icon_pos1[f][DELAY], DEC);
      display1.drawBitmap(icon_pos1[f][XPOS], icon_pos1[f][YPOS], bitmap, w, h, WHITE);
      display1.display();
    }
    delay(5000);
    /*
        // then erase it + move it
        for (uint8_t f=0; f< NUMFLAKES; f++) {
          display0.drawBitmap(icon_pos0[f][XPOS], icon_pos0[f][YPOS], bitmap, w, h, BLACK);
          // move it
          icon_pos0[f][YPOS] += icon_pos0[f][DELAY];
          // if its gone, reinit
          if (icon_pos0[f][YPOS] > DISPLAY_H) {
            icon_pos0[f][XPOS] = random(DISPLAY_W);
            icon_pos0[f][YPOS] = 0;
            icon_pos0[f][DELAY] = random(5) + 1;
          }
        }

        for (uint8_t f=0; f< NUMFLAKES; f++) {
          display1.drawBitmap(icon_pos1[f][XPOS], icon_pos1[f][YPOS], bitmap, w, h, BLACK);
          // move it
          icon_pos1[f][YPOS] += icon_pos1[f][DELAY];
          // if its gone, reinit
          if (icon_pos1[f][YPOS] > DISPLAY_H) {
            icon_pos1[f][XPOS] = random(DISPLAY_W);
            icon_pos1[f][YPOS] = 0;
            icon_pos1[f][DELAY] = random(5) + 1;
          }
        }
    */
  }
}

/*
  void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
  delay(1);
  }

  void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
    delay(1);
  }
  }

  void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    delay(1);
    color++;
  }
  }

  void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
    delay(1);
  }
  }

  void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
  }

  void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
    delay(1);
  }
  }

  void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
  }

  void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
    delay(1);
  }
  }


  void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("scroll");
  display.display();
  delay(1);

  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  }

*/

void testdrawline(LED_Display display) {
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, 0, i, display.height() - 1, WHITE);
    display.display();
    delay(1);
  }
  /*
    for (int16_t i=0; i<display.height(); i+=4) {
      display.drawLine(0, 0, display.width()-1, i, WHITE);
      display.display();
      delay(1);
    }
    delay(250);

    display.clearDisplay();
    for (int16_t i=0; i<display.width(); i+=4) {
      display.drawLine(0, display.height()-1, i, 0, WHITE);
      display.display();
      delay(1);
    }
    for (int16_t i=display.height()-1; i>=0; i-=4) {
      display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
      display.display();
      delay(1);
    }
    delay(250);

    display.clearDisplay();
    for (int16_t i=display.width()-1; i>=0; i-=4) {
      display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
      display.display();
      delay(1);
    }
    for (int16_t i=display.height()-1; i>=0; i-=4) {
      display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
      display.display();
      delay(1);
    }
    delay(250);

    display.clearDisplay();
    for (int16_t i=0; i<display.height(); i+=4) {
      display.drawLine(display.width()-1, 0, 0, i, WHITE);
      display.display();
      delay(1);
    }
    for (int16_t i=0; i<display.width(); i+=4) {
      display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE);
      display.display();
      delay(1);
    }
    delay(250);

  */
}


