/**
 * Geiger Counter Pin VIN <-> Pin 2 (Arduino)
 */
#include <SPI.h>
#include <Wire.h>

volatile unsigned long hits = 0; // Tube events

unsigned long DAY = 8640000; // 1 Day
unsigned long HOUR = 360000; // 1 Hour
unsigned long MINUTE = 60000; // 1 Minute
unsigned long TICK_HEIGHT = 1000; // 1 Minute


unsigned long sampleRate = 1000;
unsigned long sampleHits = 0; // Hits in one sample
unsigned long previousTime;
unsigned long previousHits; // Time measurement

const int inputPin = 2; // Has to use PIN 2 because it supports interrupts

void ISR_impulse() { // Captures count of events from Geiger counter board
  hits++;
  // Serial.println(hits);
}

void setup()   {
  Serial.begin(9600);

  previousTime = millis();
  
  pinMode(inputPin, INPUT);                                                // Set pin for capturing Tube events
  interrupts();                                                            // Enable interrupts
  attachInterrupt(digitalPinToInterrupt(inputPin), ISR_impulse, FALLING); // Define interrupt on falling edge
}


void loop() {
  unsigned long currentTime = millis();
  if(currentTime < previousTime)
  {
    // means millis() overflowed after 50 days
    previousTime = currentTime;

    return;
  }
  
  if(currentTime > (previousTime + sampleRate))
  {
      sampleHits = hits - previousHits;    

//    Serial.println("----");
//    Serial.print(currentTime);
//    Serial.println(previousTime);
//    Serial.print(0); // print a baseline for scaling
//    Serial.print(",");
//    Serial.print(1000); // print a baseline for scaling
//    Serial.print(",");
//    Serial.print(2000); // print a baseline for scaling
//    Serial.print(",");
//    Serial.print(3000); // print a baseline for scaling
//    Serial.print(",");
//    Serial.print(4000); // print a baseline for scaling
//    Serial.print(",");
//    Serial.print(5000); // print a baseline for scaling
//    Serial.print(",");
//    Serial.print(6000); // print a baseline for scaling
//    Serial.print(",");
//    Serial.print(7000); // print a baseline for scaling
//    Serial.print(",");
//    Serial.print(8000); // print a baseline for scaling
//    Serial.print(sampleRate);
//    Serial.print(",");
      Serial.print(sampleHits);
      Serial.print(",");
      Serial.print(currentTime%MINUTE==0?TICK_HEIGHT:0);
      Serial.print(",");
      Serial.print(currentTime%HOUR==0?TICK_HEIGHT:0);
      Serial.print(",");
      Serial.print(currentTime);
     
      Serial.println("");

    previousHits = hits;
    previousTime = currentTime;
  }

  delay(1000);
}
