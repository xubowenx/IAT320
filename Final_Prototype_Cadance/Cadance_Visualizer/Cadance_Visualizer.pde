import processing.serial.*;

Serial myPort;

String data;
float x, y, z, acc;

color[] presets = {
  color(255, 255, 255), 
  color(255, 167, 36), 
  color(228, 28, 235), 
  color(74, 207, 255), 
  color(255, 61, 68)
};

int currPreset = 0;

void setup() {
  size(600, 600);

  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.bufferUntil('\n');
  
  background(0);
  
  initializeParticles();
}

void draw() {
  while (myPort.available() > 0) {
    data = myPort.readStringUntil('\n');
  }

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
  
  updateParticles();
}
