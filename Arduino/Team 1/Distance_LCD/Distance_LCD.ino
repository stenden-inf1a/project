#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#include <NewPing.h>
#define Trig  13 
#define Echo  12 
#define Distance 200 

#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

int n = 1;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
NewPing sonar(Trig, Echo, Distance); 

void setup()
{
 lcd.begin (16,2); //  <<----- My LCD was 16x2

 
// Switch on the backlight
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home (); // go home


}

void loop()
{
  if(sonar.ping_cm() != 0){ 
  lcd.setCursor (0,0); 
  lcd.print(sonar.ping_cm());
  lcd.print("cm");
  delay(100);
  lcd.print("                ");
  lcd.setCursor (0,1); 
  lcd.setBacklight(HIGH);     // Backlight on
  lcd.print("Fuck team 2"); 
}
}
