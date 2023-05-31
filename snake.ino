
int sz = 1; //snake size 
int lives = 3; // snake lives
int snakex[64], snakey[64]; //keeps snake's x and y it's kind of like a loop so snakex[-1] = snakex[63] in my implementation
int headIndex = 0; // keeps the index of the snake's head 
int backIndex = 0; // keeps the index of the snake's last part / LED 
bool snakeBody[8][8] = {}; //keeps a boolean representation of the snake's body
bool ate = true;
int foodx = -1, foody = -1;

/* I will store my snake in a queue like structure, where I can pop_back  and  push_front as it moves to new locations. 
 *  since in Arduino i could not find a library to have implementation of c++ libraries like vectors and queues, I will be implementing it 
 *  using two arrays of snakex and snakey that are looped in my definition, e.g. snakex[-1] = snakex[63] somehow like python arrays. 
 */

 //dirextions 
 int dirx[4] = {0, 1, 0, -1};
 int diry[4] = {1, 0, -1, 0};
 int dir = -1;

 byte start = false;

 // push button Pins
const int LEFT = A5;
const int RIGHT = A4;
const int DEBOUNCE_DELAY = 60; // in milliseconds

//LED pins 
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};
const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6};

void pop_back() {
  backIndex = (backIndex + 1) % 64;
}

void push_front(int x, int y) {
  headIndex = (headIndex + 1) % 64;
  snakex[headIndex] = x;
  snakey[headIndex] = y;
}

void setup() {
  //setting up snake's initial position
  snakex[0] = snakey[0] = 3;
  snakeBody[3][3] = true;
  
  //setting up LED pins 
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
  }

  //setting up the push buttons 
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);

  Serial.begin(115200);
}

//coppied from previous assignment 
//when called displays the patter on LED with certain brightness
void display(byte pattern[8][8], int brightness[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) 
      if (pattern[i][j]) {
        digitalWrite(CATHODE_PINS[j], LOW);
        digitalWrite(ANODE_PINS[i], LOW);
        delayMicroseconds(brightness[i][j]);
        digitalWrite(ANODE_PINS[i], HIGH);
        digitalWrite(CATHODE_PINS[j], HIGH);
      }
      else {
        digitalWrite(CATHODE_PINS[j], HIGH);
        digitalWrite(ANODE_PINS[i], HIGH);
      }
    
  }

}

//coppied from the switch debounce code 
bool read_left_button() {
  // Terminology: "reading" refers to a raw reading of the input pin. A "reading
  // change" is when the reading is different from last time we took a reading
  // (i.e., last loop iteration). The "button_state" refers to the (debounced)
  // state of the button.

  int BUTTON = LEFT;

  static int counter = 0;              // count (debounced) button presses
  static byte button_state = HIGH;
  static byte last_reading = HIGH;
  static long last_reading_change = 0;

  byte reading = digitalRead(BUTTON);
  unsigned long now = millis();

  // Ignore button_state changes within DEBOUNCE_DELAY milliseconds of the last
  // reading change, otherwise accept.
  if (now - last_reading_change > DEBOUNCE_DELAY) {
    button_state = reading;
  }


  // Prepare for next loop
  if (reading != last_reading) last_reading_change = now;
  last_reading = reading;

  return button_state == LOW;
}

//coppied from the switch debounce code 
bool read_right_button() {
  // Terminology: "reading" refers to a raw reading of the input pin. A "reading
  // change" is when the reading is different from last time we took a reading
  // (i.e., last loop iteration). The "button_state" refers to the (debounced)
  // state of the button.

  int BUTTON = RIGHT;

  static int counter = 0;              // count (debounced) button presses
  static byte button_state = HIGH;
  static byte last_reading = HIGH;
  static long last_reading_change = 0;

  byte reading = digitalRead(BUTTON);
  unsigned long now = millis();

  // Ignore button_state changes within DEBOUNCE_DELAY milliseconds of the last
  // reading change, otherwise accept.
  if (now - last_reading_change > DEBOUNCE_DELAY) {
    button_state = reading;
  }


  // Prepare for next loop
  if (reading != last_reading) last_reading_change = now;
  last_reading = reading;

  return button_state == LOW;
}

//progresses the snake one step
bool progress() {
  int x = (snakex[headIndex] + dirx[dir]);
  int y = (snakey[headIndex] + diry[dir]);
  if (x < 0 || x >= 5) 
    return true;
  if (y < 0 || y >= 8) 
    return true;

  if (snakeBody[x][y])
    return true;
  push_front(x, y);

  if (x != foodx || y != foody) 
    pop_back();
  else {
    ate = true;
    sz += 1;
  }

  for (int i = 0;  i < 8; i++)
    for (int j = 0; j < 8; j++)
      snakeBody[i][j] = false;
  for (int i = backIndex; i != headIndex; i = (i + 1) % 64) 
    snakeBody[snakex[i]][snakey[i]] = true;
  snakeBody[snakex[headIndex]][snakey[headIndex]] = true;
  return false;
}

void generate_food() {
  int rnd = random(0, 40 - sz);
  int cnt = 0; 
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 8; j++) 
      if (!snakeBody[i][j]) {
        if (cnt == rnd) {
          foodx = i; 
          foody = j;
          ate = false;
          return;
        }
        cnt++;
      }
}

void loop() {
  byte ledOn[8][8] = {};
  int brightness[8][8] = {};
  int curTime = millis();
  static int lastTime = 0;
  static bool start = false, hit = false;
  static bool curRead = false;
  static int tmp = 40;
  sz = tmp;
  if (sz == 40) { //won the game
    for (int sum = 0; sum < 16; sum++) {
       byte winLedOn[8][8] = {};
       int winBrightness[8][8] = {};
       for (int i = 0; i < 8; i++) 
        for (int j = 0; j < 8; j++) 
          if (i + j == sum) {
            winLedOn[i][j] = true;
            winBrightness[i][j] = 15;
          }
        int t = millis();
        while (millis() - t < 500) 
          display(winLedOn, winBrightness);
    }
    sz = tmp = 1;
  }
  if (!start) {
    if (read_left_button()) {
      start = true;
      dir = 2;
      lastTime = millis();
      curRead = true;
    }
    else if (read_right_button()) {
      start = true;
      dir = 0;
      lastTime = millis();
      curRead = true;
    }
  }

  if (hit) {
     if (read_left_button()) {
      hit = false;
      dir = (dir - 1 + 4) % 4;
      lastTime = millis();
      curRead = true;
    }
    else if (read_right_button()) {
      hit = false;
      dir = (dir + 1 + 4) % 4;
      lastTime = millis();
      curRead = true;
    }
    
  }

  if (start && ate) {
    generate_food();
  }

  if (!hit && start && !curRead && read_left_button()) {
    curRead = true;
    dir = (dir - 1 + 4) % 4;
    lastTime = millis();
  }
  if (!hit && start && !curRead && read_right_button()) {
    curRead = true;
    dir = (dir + 1) % 4;
    lastTime = millis();
  }

  if (!hit && start && curTime - lastTime > 1000) {
    //progress the snake one step 
    hit = progress();
    if (hit) {
      lives -= 1;
    }
    curRead = false;
    lastTime = curTime;
  }
  
  ledOn[snakex[headIndex]][snakey[headIndex]] = true;
  brightness[snakex[headIndex]][snakey[headIndex]] = 1;
  for (int i = backIndex; i != headIndex; i = (i + 1) % 64) {
    ledOn[snakex[i]][snakey[i]] = true; 
    brightness[snakex[i]][snakey[i]] = 100; 
  }

  for (int i = 5; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (j / 3 + 1 <= lives && j % 3 != 2) {
        ledOn[i][j] = true;
        brightness[i][j] = 7;
      }
    }
  }

  if (!ate) {
    ledOn[foodx][foody] = true;
    brightness[foodx][foody] = 5;
  }
  display(ledOn, brightness);
  //lost the game 
  if (lives == 0) {
    start = false;
    snakex[0] = snakey[0] = 3;
    headIndex = backIndex = 0;
    sz = 1;
    hit = false;
    lastTime = 0;
    curRead = false;
    for (int i = 0; i < 8; i++)
     for (int j = 0; j < 8; j++)
      snakeBody[i][j] = false;
    snakeBody[3][3] = true;
    lives = 3;
    ate = true;
    foodx = foody = -1;
  }

  tmp = sz;
  
}
