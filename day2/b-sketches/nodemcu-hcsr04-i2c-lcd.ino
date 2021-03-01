// the libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// defines pins numbers
const int trigPin = D4;  
const int echoPin = D5;  
// scl - d1
// sda - d2

// defines variables
long duration;
int distance;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication

  lcd.init();    // initialize the lcd                    
  
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.setCursor(1,0); //lcd.setCursor(x,y)
  lcd.print("SELAMAT DATANG "); // Start Print text to Line 1
  lcd.setCursor(5,1); //lcd.setCursor(x,y)
  lcd.print("KE PMJ"); // Start Print text to Line 2
  delay(1000); //delay 1sec

}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
    
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // Prints the distance on the LCD
  lcd.init(); 
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print("cm        ");
  
  delay(1000);
}

