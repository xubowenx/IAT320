#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#define LED_PIN    A1

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

bool light = true;
bool dark = false;

class Smooth {
  private:
    float *window;
    size_t window_size;
    int window_pos;
    float window_sum;
  public:
    Smooth(size_t n) {
      window_size = n;
      window_pos = 0;
      window = new float[window_size]();
      window_sum = 0;
    }
    ~Smooth() {
      delete[] window;
    }
    float update(float x) {
      window_sum = window_sum - window[window_pos] + x;
      window[window_pos] = x;
      window_pos = (window_pos + 1) % window_size;
      return window_sum / window_size;
    }
};

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

float x, y, z, smooth_x, smooth_y, smooth_z;
Smooth sx(10);
Smooth sy(10);
Smooth sz(10);

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  //strip.setBrightness(50); 
}

void loop() {

  x = CircuitPlayground.motionX();
  y = CircuitPlayground.motionY();
  z = CircuitPlayground.motionZ();

  smooth_x = sx.update(x);
  smooth_y = sy.update(y);
  smooth_z = sz.update(z);

  float acc = abs(smooth_x) + abs(smooth_y) + abs(smooth_z);


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

  //float brightness = map(acc, 9.8, 15, 0, 40);
  
  for (int i = 0; i < 10; i++) {
    strip.setPixelColor(i, presets[preset][i % 4][0], presets[preset][i % 4][1], presets[preset][i % 4][2]);
    strip.setBrightness(acc*3-20);
    strip.show();
  }

  Serial.print(preset);
  Serial.print(" ");
  Serial.print(smooth_x);
  Serial.print(" ");
  Serial.print(smooth_y);
  Serial.print(" ");
  Serial.print(smooth_z);
  Serial.print(" ");
  Serial.println(acc);
}
