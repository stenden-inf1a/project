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

LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
NewPing sonar(Trig, Echo, Distance);

int count = 1;

#define MoterpinA2 2
#define MoterpinA  3
#define MoterpinB2  4
#define MoterpinB  9

void setup()
{
  lcd.begin (16, 2); //  <<----- My LCD was 16x2

  Serial.begin(115200);

  pinMode(MoterpinA, OUTPUT);
  pinMode(MoterpinA2, OUTPUT);
  pinMode(MoterpinB, OUTPUT);
  pinMode(MoterpinB2, OUTPUT);

  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home (); // go home


}

void loop()
{
  //--------------------------LCD Geeft afstand forward facing sensor aan--------------------------
  if (sonar.ping_cm() != 0) {
    lcd.setCursor (0, 0);
    lcd.print(sonar.ping_cm());
    lcd.print("cm");
    lcd.print("   ");
    lcd.print(count);
    delay(100);
    lcd.print("                ");
    lcd.setCursor (0, 1);
    lcd.setBacklight(HIGH);     // Backlight on
    lcd.print("Fuck team 2");
  }
  //--------------------------Rij richting/snelheid wordt bepaald op basis van afstand--------------------------
  if (sonar.ping_cm() > 30 && sonar.ping_cm() != 0) {
    count = 1;
  }
  if (sonar.ping_cm() > 0 && sonar.ping_cm() < 15 && sonar.ping_cm() != 0) {
    count = 0;
  }
  if (sonar.ping_cm() > 15 && sonar.ping_cm() < 30 && sonar.ping_cm() != 0) {
    count = 3;
  }

  //--------------------------Debug sonar en richting--------------------------
  //count = Serial.read();
  Serial.print("count = ");
  Serial.print(count);
  Serial.print("     ");

  //afstand sonarmeter
  delay(50);
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");


  //--------------------------Switch case die count variabele aan de rijrichting linkt--------------------------
  switch (count) {
    case 1:
      forward();
      break;
    case 2:
      backward();
      break;
    case 3:
      right();
      break;
    case 4:
      left();
      break;
    default:
      still();
      break;
  }
}
//--------------------------functies voor rijrichting--------------------------
void still() {
  digitalWrite(MoterpinA, LOW);     // linkerwiel vooruit
  digitalWrite(MoterpinA2, LOW);    // linkerwiel achteruit
  digitalWrite(MoterpinB, LOW);    // rechterwiel vooruit
  digitalWrite(MoterpinB2, LOW);    // rechterwiel achteruit
}
void forward() {
  digitalWrite(MoterpinA, HIGH);     // linkerwiel vooruit
  digitalWrite(MoterpinA2, LOW);    // linkerwiel achteruit
  digitalWrite(MoterpinB, HIGH);    // rechterwiel vooruit
  digitalWrite(MoterpinB2, LOW);    // rechterwiel achteruit
}
void backward() {
  digitalWrite(MoterpinA, LOW);     // linkerwiel vooruit
  digitalWrite(MoterpinA2, HIGH);    // linkerwiel achteruit
  digitalWrite(MoterpinB, LOW);    // rechterwiel vooruit
  digitalWrite(MoterpinB2, HIGH);    // rechterwiel achteruit
}
void right() {
  analogWrite(MoterpinA, 153);     // linkerwiel vooruit
  analogWrite(MoterpinB2, 153);    // rechterwiel achteruit
}

void left() {
  analogWrite(MoterpinA2, 153);    // linkerwiel achteruit
  analogWrite(MoterpinB, 153);    // rechterwiel vooruit
}




