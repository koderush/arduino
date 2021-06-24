#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int TrigPin = 6;
const int EchoPin = 7;
float range;
char buf[256];
void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("DISTANCE:");
}
void loop()
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  range = pulseIn(EchoPin, HIGH) / 58.0; //The echo time is converted into cm
  if(range < 0)
  {
    return;
  }

  Serial.print("Distance:");
  Serial.print(range);
  Serial.print("cm");
  Serial.println();

  // lcd.clear();
  lcd.setCursor(0, 1); //Display position
  lcd.print(range);
  lcd.print(" cm       ");  
  lcd.display();

  delay(100);
}
