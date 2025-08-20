var r = 0;
var g = 0;
var b = 155;

function setup() {
  createCanvas(600, 400);
}

function draw() {
  // Map colors to mouse position
  r = map(mouseX, 0, width, 0, 255);
  g = map(mouseY, 0, height, 0, 255);
  b = map(mouseX, 0, width, 255, 0);

  // Background changes with cursor
  background(r, g, b);

  // Circle follows mouse
  fill(250, 118, 222);
  ellipse(mouseX, mouseY, 64, 64);
}
