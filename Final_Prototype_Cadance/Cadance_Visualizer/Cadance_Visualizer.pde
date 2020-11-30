import processing.serial.*;

Serial myPort;

//stores data from Serial
String data;

//stores accelerometer data
float x, y, z, acc;

//stores opacity of background color
int alpha;

//color presets to match LEDs
color[] presets = {
  color(255, 255, 255), 
  color(255, 167, 36), 
  color(228, 28, 235), 
  color(74, 255, 122), 
  color(255, 61, 68)
};

int currPreset = 0;

void setup() {
  size(800, 800);

  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.bufferUntil('\n');
}

void draw() {

  while (myPort.available() > 0) {
    data = myPort.readStringUntil('\n');
  }
  
  //if data is being received, update values
  if (data != null) {
    float[] nums = float(split(trim(data), ' '));
    currPreset = int(nums[0]);
    x = nums[1];
    y = nums[2];
    z = nums[3];
    acc = nums[4];
  }

  println("X: " + x);
  println("Y: " + y);
  println("Z: " + z);
  println("Total: " + acc);

  //map total acceleration to opacity of color
  alpha = int(map(acc, 9.8, 45, 0, 255));
  
  background(0);
  fill(presets[currPreset], alpha);
  rect(0, 0, width, height);
}