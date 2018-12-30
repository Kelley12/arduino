/*
  Keypad LCD
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// creating lcd instance "lcd" from the LiquidCrystal_I2C class constructor
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address and LCD Size

void setup()
{
// initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome !");
  delay(2000);
  // initialize serial port
  Serial.begin(9600);
  // the following function is used to find the LCD Contoller address
  //scanForI2CAddress();
}

void loop()
{
  displaySerialPortOnLCD();
}

void scanForI2CAddress()
{
  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;
  Wire.begin();
  for (byte i = 1; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);
    }
  }
  Serial.println ("End of Scanning");
}

void displaySerialPortOnLCD()
{
  if (Serial.available()) {
    delay(100); // wait a bit for the entire message to arrive
    lcd.clear(); // clear the screen

    while (Serial.available() > 0)
    { // read each character from the serial port and display it in the LCD
      lcd.write(Serial.read());
    }
  }
}