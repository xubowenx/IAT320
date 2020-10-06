#include <Adafruit_CircuitPlayground.h>

int vals[8]= {3,2,0,1,6,9,10,12};
float pitches[8] = {211,245,280,333,388,440,522,600}; //colors

//int c =0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

}

void loop() {

  for (int i= 0; i <8; i++){
    int x = CircuitPlayground.readCap(vals[i]);
    if (x>1000) {
      CircuitPlayground.playTone(pitches[i], 200);
    }
    Serial.println(x);
  }

  delay(500);

}
