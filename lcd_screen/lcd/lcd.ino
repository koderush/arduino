#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("ADAPTIVE ALARMS");

}
void loop()
{
  // Turn off the display:
  //lcd.noDisplay();
  // Turn on the display:
  lcd.setCursor(0, 1); //Display position
  lcd.print("PASON SYSTEMS");
  lcd.display();
  delay(500);
}
