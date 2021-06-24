#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.display();

  myservo.attach(9);
}

void loop()
{
  moveServo(0);

  moveServo(45);

  moveServo(90);

  moveServo(135);

  moveServo(180);
}

void moveServo(int pos)
{
  lcd.setCursor(0,0);
  char buf[256];
  sprintf(buf,"POSISTION: %4d", pos); 
  lcd.print(buf);
  myservo.write(pos);
  delay(1000);
}

