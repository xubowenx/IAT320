#include <Adafruit_CircuitPlayground.h>

int presets[3][3][3] = {     //presets/rows,colors/inside
  {
   {0,255,0},
   {255,0,0},
   {0,0,255}
  },
  {
   {0,225,111},
   {55,0,210},
   {222,0,5}
  },
  {
    {0,0,255},
    {0,44,138},
    {66,0,38}
  }
};

int preset = 0;
bool lastRightPress = false;
bool lastLeftPress = false;

void setup() {
 Serial.begin(9600);
 CircuitPlayground.begin();
}

void loop() {
  float total = abs(CircuitPlayground.motionX()) +
  abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());

  if (total > 25){
    preset =  rand() % 3;
  }

  Serial.println(total);
  
//  if (total > 10) {                                                      
//  // do something
//  }

//  if (CircuitPlayground.leftButton()) {
//  Serial.println("Left button pressed!");
//  }

  
  bool rightPress = CircuitPlayground.rightButton();  
  if (rightPress && (lastRightPress == false)) {
    preset = (preset + 1) % 3;
  }
  
  lastRightPress = rightPress;

  bool leftPress = CircuitPlayground.leftButton();
  if (leftPress && (lastLeftPress == false)) {
    preset = ((preset - 1)+3) % 3;
  }
  lastLeftPress = leftPress;
  
  for (int i = 0; i <10; i++) {
    CircuitPlayground.setPixelColor(i,presets[preset][i%2][0], presets[preset][i%2][1],presets[preset][i%2][2]);
  }

  delay(10);
}
