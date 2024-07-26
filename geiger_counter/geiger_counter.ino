/* 
 Modified by KR
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

volatile unsigned long counts = 0;  // Tube events
unsigned long cpm = 0;              // CPM
unsigned long previousMillis;       // Time measurement
const int inputPin = 3;             // geiger is on this pin?
unsigned int thirds = 0;
unsigned long minutes = 0;
unsigned long hours = 0;
unsigned long days = 0;
unsigned long start = 0;

#define LOG_PERIOD 1000  //Logging period in milliseconds
#define MINUTE_PERIOD 60000
#define HOUR_PERIOD 3600000
#define DAY_PERIOD 86400000

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);


void ISR_impulse() {  // Captures count of events from Geiger counter board
  counts++;
  Serial.println(counts);
  // ledPrintln(0, 0, String(counts));
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  display.clearDisplay();

  Serial.println("booting...");
  Serial.println("measuring");
  pinMode(inputPin, INPUT);  // Set pin for capturing Tube events
  interrupts();
  attachInterrupt(digitalPinToInterrupt(inputPin), ISR_impulse, FALLING);  // Define interrupt on falling edge
  unsigned long clock1 = millis();
  start = clock1;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  // Serial.println("looping...");

  if (currentMillis - previousMillis > LOG_PERIOD) {

    previousMillis = currentMillis;
    // Serial.print("previousMillis: ");
    // Serial.println(String(previousMillis));
    minutes = (previousMillis - start) / MINUTE_PERIOD;
    hours = (previousMillis - start) / HOUR_PERIOD;
    days = (previousMillis - start) / DAY_PERIOD;

    // Serial.print("minutes: ");
    // Serial.println(String(minutes));

    //cpm = counts * MINUTE_PERIOD / LOG_PERIOD; this is just counts times 3 so:

    cpm = counts / minutes;
    // Serial.print("Total clicks since start: ");
    // Serial.println(String(counts));
    display.clearDisplay();
    {
      ledPrint(0, 0, "Counts: " + String(counts));
      ledPrint(0, 16, "Minutes: " + String(minutes));
      ledPrint(0, 32, "Days: " + String(days));
      ledPrint(0, 48, "Avg: " + String(counts / (minutes + 0.01)) + " / min");
    }
    display.display();
    // Serial.print("Rolling CPM: ");
    // Serial.println(String(cpm));

    //    if ( thirds > 2) {
    //      counts = 0;
    //      thirds = 0;
    //    }
  }
}

void ledPrint(uint8_t startX, uint8_t startY, String s) {

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(startX, startY);
  display.print(s);
}
