#include <Adafruit_CircuitPlayground.h>

void setup() {

  Serial.begin(9600);

  CircuitPlayground.begin();         
}

void loop() {

  int mi = 4;
  int ma = 300;
  int light = CircuitPlayground.lightSensor();
  int n = (int)map(light, mi, ma, 0,9);
    
  Serial.println(n);
  
  for (int i=0; i < 10; i++){
    if (i <= n){
      CircuitPlayground.setPixelColor(i,0,0,255);
    }
    else {
      CircuitPlayground.setPixelColor(i,0,0,0);
    }
  }
  
  delay(20);
}
