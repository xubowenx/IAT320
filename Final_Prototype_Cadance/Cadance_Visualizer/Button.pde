class Button {
  PVector pos;
  float w = 30;
  float h = 30;
  String direction;
  float alpha = 30;
  boolean pressed = false;

  Button(String direction, float x, float y) {
    pos = new PVector(x, y);
    this.direction = direction;
  }

  void display() {
    fill(255, 50);
    noStroke();

    pushMatrix();
    translate(pos.x, pos.y);
    if (direction == "left") scale(-1, 1);
    if (direction == "right") scale(1, 1);
    
    if (mouseX >= pos.x - w/2 && mouseX <= pos.x + w/2 && 
      mouseY >= pos.y - h/2 && mouseY <= pos.y + h/2) {
      pressed = true;
      increaseOpacity(150);
    } else {
      pressed = false;
      decreaseOpacity(30);
    }
    
    fill(255, alpha);
    ellipse(0, 0, w, h);

    stroke(0);
    strokeWeight(2);
    noFill();
    //triangle(0, 0, w, h/2, 0, h);
    beginShape();
    vertex(-w/10, -h/4);
    vertex(w/6, 0);
    vertex(-w/10, h/4);
    endShape();
    popMatrix();
  }
  
  void increaseOpacity(int max){
    if (alpha < max) alpha += 4;
  }
  
  void decreaseOpacity(int min){
    if (alpha > min) alpha -= 4;
  }
  
  boolean pressed(){
    return pressed;
  }
}
