let x = 0;
let y = 200;
let speed = 3;
let direction = 1; // 1 = right, -1 = left

let soundRight; // left→right
let soundLeft;  // right→left

function preload() {
  soundRight = loadSound('assets/right.mp3');
  soundLeft = loadSound('assets/left.mp3');
}

function setup() {
  createCanvas(600, 400);
  userStartAudio(); // ensures audio can play after user gesture
}

function draw() {
  background(50);

  // Draw ball
  fill(200, 100, 250);
  ellipse(x, y, 50, 50);

  // Move ball
  x += speed * direction;

  if (x > width - 25) {
    direction = -1;
    // Stop the other sound and play left sound
    if (soundRight.isPlaying()) soundRight.stop();
    if (!soundLeft.isPlaying()) soundLeft.play();
  }

  if (x < 25) {
    direction = 1;
    // Stop the other sound and play right sound
    if (soundLeft.isPlaying()) soundLeft.stop();
    if (!soundRight.isPlaying()) soundRight.play();
  }
}
