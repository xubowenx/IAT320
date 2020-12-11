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

ParticleVisualizer particleVis = new ParticleVisualizer();
MetaMatterVisualizer metaVis = new MetaMatterVisualizer();

final int PARTICLE = 0;
final int BLANK = 1;

int[] screens = {PARTICLE, BLANK};

int screen = 0;

void setup() {
  size(600, 600);

  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.bufferUntil('\n');
  
  background(0);
  
  particleVis.initialize();
}

float changeAcc;

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
  
  //changeAcc = diffAcc();

  println("X: " + x);
  println("Y: " + y);
  println("Z: " + z);
  println("Total: " + acc);
    //println("Diff: " + diffAcc());

  
  switch (screen) {
    case(PARTICLE):
     particleVis.display();
     break;
     
    case(BLANK):
     metaVis.display();
     break;
  }
}

  boolean moving(){
    return acc > 16;
  }

void keyPressed(){
  if (key == CODED){
    if (keyCode == RIGHT) screen = (screen + 1) % screens.length;
    if (keyCode == LEFT) screen = ((screen - 1) + screens.length) % screens.length;
  }
}
