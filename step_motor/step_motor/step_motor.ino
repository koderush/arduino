#include <Stepper.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// change this to fit the number of steps per revolution
// for your motor
int stepsPerRevolution = 2048;

// initialize the stepper library on pins 2 through 5:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// number of steps the motor has taken
int stepCount = 0;

void setup()
{
  myStepper.setSpeed(60);
  
  // initialize the serial port:
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.display();
}
void loop()
{
  lcd.setCursor(0,0);
  lcd.print("STEP MOTOR!%#$");
  myStepper.step(1);
  delay(20);
}

