//nodemcu SCL - D1 ; SDA - D2
#include <Wire.h>   // This library is already built in to the Arduino IDE
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
 
  lcd.init();    // initialize the lcd                    
  
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.setCursor(1,0); //lcd.setCursor(x,y)
  lcd.print("SELAMAT DATANG "); // Start Print text to Line 1
  lcd.setCursor(5,1); //lcd.setCursor(x,y)
  lcd.print("KE PMJ"); // Start Print text to Line 2

}

void loop()
{
}
