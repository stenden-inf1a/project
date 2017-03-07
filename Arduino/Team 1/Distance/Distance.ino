#include <NewPing.h>

#define Trig  13 
#define Echo  12 
#define Distance 200 

NewPing sonar(Trig, Echo, Distance); 

void setup() {
  Serial.begin(115200); // 
}

void loop() {
  if(sonar.ping_cm() != 0){
  delay(50);                     
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
  }
}
