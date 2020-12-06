/*
  * Visualizer 2: Meta Matter
 *
 * Original code written by OpenProcessing user @leithBA and published on 2019/10/19
 * https://www.openprocessing.org/sketch/773556
 *
 * Reformatted from P5.js to Processing. Modified to continually change colour and respond to user input for colour palette.  
 */
//

class MetaMatterVisualizer implements Visualizer {
  float res = 100; //idk what this is but it slows everything down ++ 
  float amp = 6; //space between rings
  float iter = 20; //volatility
  float xOffset = 0;
  float yOffset = 0;
  float speed = 0.002;
  float time = 0;

  float resizeSpeed = 1;

  void initialize() {
  }

  float zoff;

  void display() {

    //newAcc = map(acc, 9.8, 60, 0, 3);
    if (moving()) {
      amp += 0.01;
      iter += 0.01;
    }

    background(0);

    translate(width / 2, height / 2);
    time += speed;
    xOffset = sin(time * 0.05) * 100 + 5000;
    yOffset = cos(time * 0.05) * 100 + 5000;
    fill(0, 0);

    color from = presets[currPreset];
    color to;

    for (int j = 0; j < 50; j++) {
      beginShape();

      for (int i = 0; i < res; i++) {
        
        if (currPreset == 0) {
          to = color(255, 255, 255, 160);
        } else if (currPreset == 1) {
          to = color(255, 255, 133);
        } else if (currPreset == 2) {
          to = color(63, 0, 199);
        } else if (currPreset == 3) {
          to = color(83, 28, 235);
        } else if (currPreset == 4) {
          to = color(255, 174, 61);
        } else {
          to = presets[currPreset];
        }

        float n = noise(xOffset + sin(i * TWO_PI / res) * 0.01 * j, yOffset + cos(i * TWO_PI / res) * 0.01 * j, time);
        strokeWeight(j / 50);
        //stroke(lerpColor(from, to, j*0.01));
        stroke(lerpColor(from, to, sin(zoff)));
        float x = sin(i * TWO_PI / res) * j * amp * n + 1;
        float y = cos(i * TWO_PI / res) * j * amp * n + 1;
        vertex(x, y);
      }
      endShape(CLOSE);
    }

    zoff += 0.02;
  }
}

float lastAcc;

float diffAcc() {
  float diff = lastAcc / acc;
  lastAcc = acc;
  return diff;
}
