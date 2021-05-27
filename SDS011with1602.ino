// Arduino-based PM sensor station with Nova SDS011 PM sensor and I2C LCD 1602 display
// Cally Sophie
// Contains code by nick1415: https://www.instructables.com/Simple-Air-Pollution-Monitor-Using-an-Arduino-Uno-/


// Uses SDS011 library v 0.0.5. by R. Zschiegner
#include "SDS011.h"
// Uses Liquid Crystal I2C library v 1.1.2. by Frank da Brabander
#include <LiquidCrystal_I2C.h>

// Sets the LCD address to 0x27 and a 16 chars and 2 line display
// Check your LCD's I2C address - it may be 0x3F or something else
// LCD's I2C adaptor's SCL and SDA pins connected to Arduino SCL and SDA pins
LiquidCrystal_I2C lcd(0x27,16,2);  

// Creates two floats for data from sensor
float p10, p25;
int error;
SDS011 my_sds;

void setup() {
//  Sets pins for sensor - swap pins if sensor doesn't give out data
  my_sds.begin(2, 3);
  Serial.begin(9600);
// Sets up LCD 
  lcd.init();
  lcd.clear();         
  lcd.backlight();      
      }

void loop() {
//  Serial.println(millis()); // Uncomment line if needed to show data in Serial Monitor

  error = my_sds.read(&p25, &p10);
// Checks for data before attempting to display
  if (!error) {
// Clears LCD to remove previous error message
    lcd.clear();
//    Serial.println("PM2.5:  " + String(p25)); // Uncomment line if needed to show data in Serial Monitor
//    Serial.println("P10:   " + String(p10)); // Uncomment line if needed to show data in Serial Monitor

// Sets cursor to character 0 on line 0
    lcd.setCursor(0,0); 
// Prints "PM2.5:" and then PM2.5 reading    
    lcd.print("PM2.5: " + String(p25));
// Sets cursor to character 0 on line 1    
    lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
// Prints "PM10:" and then PM10 reading 
    lcd.print("PM10:  " + String(p10));
    delay(1000);
}
  else {
// Clears LCD to remove previous data 
    lcd.clear(); 
// Sets cursor to character 0 on line 0, then prints error message
    lcd.setCursor(0,0);  
    lcd.print("PM2.5: ERROR");
// Sets cursor to character 0 on line 1, then prints error message
    lcd.setCursor(0,1);   
    lcd.print("PM10:  ERROR");
    delay(1000);
 }

}
  
