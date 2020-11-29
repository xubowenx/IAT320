#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>

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

  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, presets[preset][i % 4][0], presets[preset][i % 4][1], presets[preset][i % 4][2]);
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
