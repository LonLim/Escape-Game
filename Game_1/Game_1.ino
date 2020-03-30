#include <Adafruit_NeoPixel.h>

#define NeoPixelPin 9

#define PixelCount 36
#define column1laser A0
#define column2laser A1
#define column3laser A2
#define column4laser A3
#define column5laser A4
#define column6laser A5

int user_answer[4] = { -1, -1, -1, -1};
int laser_answer[4] = {5, 2, 1, 0};

int match = 0;
int counter;

bool correct = false;

unsigned long delayStart = 0;

int position = -1;

int user_ans_index = 0;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;

int oldVal1 = 0;
int oldVal2 = 0;
int oldVal3 = 0;
int oldVal4 = 0;
int oldVal5 = 0;
int oldVal6 = 0;

int column1_index = 6;
int column2_index = 6;
int column3_index = 6;
int column4_index = 6;
int column5_index = 6;
int column6_index = 6;

Adafruit_NeoPixel sample = Adafruit_NeoPixel(PixelCount, NeoPixelPin, NEO_GRB + NEO_KHZ800);

void setup () {
  delayStart = millis();   // start delay
  pinMode(column1laser, INPUT);
  pinMode(column2laser, INPUT);
  pinMode(column3laser, INPUT);
  pinMode(column4laser, INPUT);
  pinMode(column5laser, INPUT);
  pinMode(column6laser, INPUT);
  Serial.begin(9600);
  sample.begin();
  sample.clear();
  sample.show();
}
void loop() {

  oldVal1 = analogRead(column1laser);
  oldVal2 = analogRead(column2laser);
  oldVal3 = analogRead(column3laser);
  oldVal4 = analogRead(column4laser);
  oldVal5 = analogRead(column5laser);
  oldVal6 = analogRead(column6laser);

  if (millis() - delayStart >= 1500) {

    val1 = analogRead(column1laser);
    val2 = analogRead(column2laser);
    val3 = analogRead(column3laser);
    val4 = analogRead(column4laser);
    val5 = analogRead(column5laser);
    val6 = analogRead(column6laser);
    delayStart = millis();
  }

  if (abs(val1 - oldVal1) < 5) {
    column1_index = sensor_values(val1);
  }
  else if (abs(val2 - oldVal2) < 5) {
    column2_index = sensor_values(val2);
  }
  else if (abs(val3 - oldVal3) < 5) {
    column3_index = sensor_values(val3);
  }
  else if (abs(val4 - oldVal4) < 5) {
    column4_index = sensor_values(val4);
  }
  else if (abs(val5 - oldVal5) < 5) {
    column5_index = sensor_values(val5);
  }
  else if (abs(val6 - oldVal6) < 5) {
    column6_index = sensor_values(val6);
  }

  if (column1_index != 6) {
    position = column1_index;
    light_up_maze();
  }
  if (column2_index != 6) {
    position = 6 + column2_index;
    light_up_maze();
  }
  if (column3_index != 6) {
    position = 12 + column3_index;
    light_up_maze();
  }
  if (column4_index != 6) {
    position = 18 + column4_index;
    light_up_maze();
  }
  if (column5_index != 6) {
    position = 24 + column5_index;
    light_up_maze();
  }
  if (column6_index != 6) {
    position = 30 + column6_index;
    light_up_maze();
  }
  for (int i = 0; i < 4; i++) {
    Serial.print(user_answer[i]);
    Serial.print(",");
  }
  Serial.println(' ');
  if (user_ans_index == 4) {
    for (int i = 0; i < 4; i++) {
      if (laser_answer[i] == user_answer[i]) {
        match ++;
      }
    }
    if ( match == 4) {
      correct = true;
      green_all_pixels();
    }
    else {
      reset_pixels();
      user_ans_index = 0;
      memset(user_answer, -1, sizeof(user_answer));
    }
  }
}

int sensor_values(int val) {
  if (val > 500) { //when the LDR is is covered
    return 0;
  }
  else if ( (400 > val) && (val > 321)) {
    return 1;
  }
  else if ( (320 > val) && (val > 220)) {
    return 2;
  }
  else if ( (210 > val) && (val > 180)) {
    return 3;
  }
  else if ( (150 > val) && (val > 125)) {
    return 4;
  }
  else if ( (100 > val) && (val > 70)) {
    return 5;
  }
  else {
    return 6;
  }
}

void light_up_maze() {
  sample.setPixelColor(position, sample.Color(150, 150, 150));
  sample.show();
  for (int i = 0; i < 4; i++) { //check if user shoot same target twice
    if (user_answer[i] == position) {
      return;
    }
  }
  user_answer[user_ans_index] = position;
  user_ans_index = user_ans_index + 1;
}

void green_all_pixels() {
  while (correct == true) {
    Serial.print(counter);
    if (counter == 3) {
      sample.clear();
      sample.show();
    }
    else {
      sample.fill(sample.Color(0, 150, 0), 0, 36);
      sample.show();
      delay(500);
      sample.clear();
      sample.show();
      delay(500);
      counter++;
    }
  }
}

void reset_pixels() {
  for (int j = 0; j < 3; j++) {
    sample.fill(sample.Color(150, 0, 0), 0, 36);
    sample.show();
    delay(500);
    sample.clear();
    sample.show();
    delay(500);
  }
}
