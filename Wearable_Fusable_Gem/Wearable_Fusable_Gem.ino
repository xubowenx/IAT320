#include <Adafruit_CircuitPlayground.h>

int presets[3][3][3] = {     //presets/rows,colors/inside
  {
   {80,155,20},
   {225,188,29},
   {222,111,25}
  },
  {
   {0,225,111},
   {55,0,210},
   {222,0,5}
  },
  {
    {0,0,255},
    {0,230,211},
    {66,0,38}
  }
};

int preset = 0;


void setup() {
 Serial.begin(9600);
 CircuitPlayground.begin();
}

void loop() {
  float total = abs(CircuitPlayground.motionX()) +
  abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());

  if (total > 20){
    preset =  rand() % 3;
  }

  //Serial.println(total);
  
  for (int i = 0; i <10; i++) {
    CircuitPlayground.setPixelColor(i,presets[preset][i%2][0], presets[preset][i%2][1],presets[preset][i%2][2]);
  }

  delay(10);
}
