/*
  * Visualizer 1: Particles
  *
  * Original code written by OpenProcessing user @aa_debdeb and published on 2015/07/29
  * https://www.openprocessing.org/sketch/378691
  *
  * Modified to add, accelerate, and assign a lifespan to particles based on accelerometer data. 
 */
 //

ArrayList<Vortex> vortices;
ArrayList<Particle> particles;

float maxForce = 10; 
float pSize = 2;

void initializeParticles(){
  vortices = new ArrayList<Vortex>();
  particles = new ArrayList<Particle>();
  
  for (int i = 0; i < 15; i++) {
    vortices.add(new Vortex(random(width), random(height)));
  }
}

void updateParticles(){
  fill(0, 30);
  noStroke();
  rect(0, 0, width, height);

  //spawn particles when motion is detected
  if (acc > 16) {
    for (int i = 0; i < acc/2; i++) {
      particles.add(new Particle());
    }
  }
  
  for (int i = particles.size()-1; i >= 0; i--) { 
    Particle p = particles.get(i);
    p.display();
    p.update();
    
    //remove particles once their lifespan is complete
    if (p.finished()){
      particles.remove(p);
    }
  }
}

class Particle {
  PVector loc;
  float alpha = 0;
  float life = random(150,255);
  float acceleration;
  color fill;

  Particle() {
    float size = map(sqrt(random(1)), 0, 1, 0, 400);
    float angle = random(TWO_PI);
    loc = new PVector(size * cos(angle) + width / 2, size * sin(angle) + height / 2);
    acceleration = map(acc, 9.8, 65, 0, 5);
    
    fill = randomColor();
  }

  void display() {
    noStroke();
    fill(fill, alpha);
    ellipse(loc.x, loc.y, pSize, pSize);
  }

  void update() {
    PVector force = new PVector(0, 0);
    for (Vortex v : vortices) {
      float d = PVector.dist(loc, v.loc);
      if (d < v.range) {
        PVector f = PVector.sub(loc, v.loc);
        f.normalize();
        f.mult(map(d, 0, v.range, 1, 0));
        if (v.clockwise) {
          f.rotate(HALF_PI);
        } else {
          f.rotate(-HALF_PI);
        }
        force.add(f);
      }
    }
    
    force.limit(maxForce);
    force.mult(acceleration);
    loc.add(force);
  }
  
  boolean finished(){
    if (alpha <= life) {
      alpha++;
    } else {
      alpha = life;
    }
    life--;
    if (life < 0) {
      return true;
    } else {
      return false;
    }
  }
}

class Vortex {
  PVector loc;
  float range;
  boolean clockwise;
  
  Vortex(float x, float y) {
    loc = new PVector(x, y);
    range = random(100, 300);
    clockwise = random(1) < 0.5 ? true: false;
  }
}

//create a more interesting colour palette based on the current preset
color randomColor(){
  color from = presets[currPreset];
  color to;
  
  if(currPreset == 0) {
    to = color(255, 255, 255, 10); 
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
  
  return lerpColor(from, to, random(1));
}

//void mouseReleased() {
//  vortices.add(new Vortex(mouseX, mouseY));
//}
