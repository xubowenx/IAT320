#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>




int presets [5][4][3] = {
  {
    {255, 255, 255},
    {255, 255, 255},
    {255, 255, 255},
    {255, 255, 255},
  },
  {
    {255, 167, 36},
    {255, 167, 36},
    {255, 167, 36},
    {255, 167, 36},
  },
  {
    {228, 28, 235},
    {228, 28, 235},
    {228, 28, 235},
    {228, 28, 235},
  },
  {
    {74, 255, 122},
    {74, 255, 122},
    {74, 255, 122},
    {74, 255, 122},
  },
  {
    {255, 61, 68},
    {255, 61, 68},
    {255, 61, 68},
    {255, 61, 68},
  },
};

int preset = 0;
bool lastRightPress = false;
bool lastLeftPress = false;


void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

}


void loop() {
  bool leftPress = CircuitPlayground.leftButton();
  if (leftPress && (lastLeftPress == false)) {
    preset = ((preset - 1) + 5) % 5;

  }
  lastLeftPress = leftPress;

  bool rightPress = CircuitPlayground.rightButton();
  if (rightPress && (lastRightPress == false)) {
    preset = (preset + 1) % 5;


  }
  lastRightPress = rightPress;

  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, presets[preset][i % 4][0], presets[preset][i % 4][1], presets[preset][i % 4][2]);
  }



}
