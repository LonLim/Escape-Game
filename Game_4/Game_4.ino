//NeoPixels
#include <Adafruit_NeoPixel.h>
#define NUM_PIXELS 14
#define PIXEL_PIN 3
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

//Stepper Motor
#include <AccelStepper.h>
#define motorPin1  4      // IN1 on the ULN2003 driver
#define motorPin2  5      // IN2 on the ULN2003 driver
#define motorPin3  6     // IN3 on the ULN2003 driver
#define motorPin4  7     // IN4 on the ULN2003 driver
#define MotorInterfaceType 8
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);
int stepper_position = 0;

//Laser and Light Dependent Resistor
#define laser 8
#define laser_sensor 9
int sensor = 0;

//Analog Joystick
#define x_direction A0
int x_value = 0;

//Red, Blue, Green Button
#define red_button 10
#define blue_button 11
#define green_button 12
int red_value = 1;
int blue_value = 1;
int green_value = 1;

//Color in RGB format
uint32_t red = pixel.Color(255, 0, 0);
uint32_t green = pixel.Color(0, 255, 0);
uint32_t blue = pixel.Color(0, 0, 255);
uint32_t yellow = pixel.Color(255, 255, 0);
uint32_t cyan = pixel.Color(0, 255, 255);
uint32_t purple = pixel.Color(250, 0, 255);
uint32_t white = pixel.Color(255, 255, 255);
uint32_t color_array[] = {red, green, blue, yellow, purple, cyan, white};
bool current_status = false;

//Start Button
#define start_button 13
bool start_game = false;

//Answer and inputs
int show_answer[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int user_answer[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int game_set[5] = {6, 7, 8, 10, 12};
int color_index;
int num_answer;
int current_set = 0;
int pos = 0;

//Delays
unsigned long startPressMillis;
const unsigned pressMillis = 20000;
unsigned long startblinkMillis = 0;
unsigned blinkMillis;

void setup() {
  // put your setup code here, to run once:
  pinMode(start_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);
  pinMode(blue_button, INPUT_PULLUP);
  pinMode(laser, OUTPUT);
  pinMode(laser_sensor, INPUT);
  Serial.begin(9600);
  stepper.setMaxSpeed(1000); // Set the maximum steps per second
  stepper.setAcceleration(200); // Set the maximum acceleration in steps per second^2
  pixel.begin();
  startblinkMillis = millis();
  num_answer = game_set[current_set];
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(start_button == '0'))
  {
    start_game = true;
  }
  while (start_game == true)
  {
    digitalWrite(laser, HIGH);
    get_color();
    show_color();
    startPressMillis = millis();
    while (millis() - startPressMillis <= pressMillis)
    {
      user_input();
      blink_or_show();
    }
    check_answer();
  }
}

void get_color() {
  for (int index = 0; index < 12; index++)
  {
    if (index < num_answer)
    {
      show_answer[index] = random(0, 6);
    }
    else
    {
      show_answer[index] = -1;
    }
  }
}

void show_color() {
  for (int index = 0; index < 12; index++)
  {
    if (show_answer[index] != -1)
    {
      pixel.setPixelColor(index, color_array[show_answer[index]]);
      pixel.show();
      delay(500);
    }
    else
    {
      pixel.setPixelColor(index, pixel.Color(0, 0, 0));
    }
  }
  delay(1000);
}

void user_input() {
  x_value = analogRead(x_direction);
  if ( x_value > 600)
  {
    pos = pos + 1;
    if (pos == num_answer)
    {
      pos = 0;
    }
  }
  if ( x_value < 400)
  {
    pos = pos - 1;
    if (pos == 0)
    {
      pos = num_answer;
    }
  }
  red_value = digitalRead(red_button);
  blue_value = digitalRead(blue_button);
  green_value = digitalRead(green_button);
  if (red_value == '0')
  {
    color_index = change_answer(user_answer[pos], 0);
    user_answer[pos] = color_index;
  }
  if (blue_value == '0')
  {
    color_index = change_answer(user_answer[pos], 2);
    user_answer[pos] = color_index;
  }
  if (green_button == '0')
  {
    color_index = change_answer(user_answer[pos], 1);
    user_answer[pos] = color_index;
  }
}

int change_answer(int currentColor, int button) { //Li Long to input swtich case

  switch (currentColor) {

    case 0: // led was red
      if (button == 0)
      {
        return 0;
      }  //red button detected, return red
      else if (button == 1)
      {
        return 3; //green button detected, return yellow
      }
      else {
        return 4; //blue button detected, return purple
      }

    case 1: // led is green
      if (button == 0) {
        return 3; //return yellow
      }
      else if (button == 1) {
        return 1; //return green
      }
      else {
        return 5; //return cyan
      }

    case 2: // led is blue
      if (button == 0) {
        return 4; //return purple
      }
      else if (button == 1) {
        return 5; //return cyan
      }
      else {
        return 2; //return blue
      }

    case 3: // led is yellow
      if (button == 0) {
        return 1; //remove red element, return green
      }
      else if (button == 1) {
        return 0; //remove yellow element, return yellow
      }
      else {
        return 6; //add blue element, return white
      }

    case 4: // led is purple
      if (button == 0) {
        return 2; //return blue
      }
      else if (button == 1) {
        return 6; //return white
      }
      else {
        return 0; //return red
      }

    case 5: // led is cyan
      if (button == 0) {
        return 6; //return white
      }
      else if (button == 1) {
        return 2; //return blue
      }
      else {
        return 0; //return green
      }

    case 6: // led is white
      if (button == 0) {
        return 5; //return cyan
      }
      else if (button == 1) {
        return 4; //return purple
      }
      else {
        return 3; //return yellow
      }

    default: // no led
      if (button == 0) {
        return 0; //red button detected
      }
      else if (button == 1) {
        return 1; //green button detected
      }
      else {
        return 2; //blue button detected
      }
  }
}

void blink_or_show() {
  for (int index = 0; index < 12; index++)
  {
    pixel.setPixelColor(index, color_array[user_answer[index]]);
    pixel.show();
  }
  if (startblinkMillis - blinkMillis >= 500)
  {
    if (current_status == false)
    {
      pixel.setPixelColor(pos, color_array[user_answer[pos]]);
      current_status = true;
      blinkMillis = startblinkMillis;
    }
    else
    {
      pixel.setPixelColor(pos, pixel.Color(0, 0, 0));
      current_status = false;
      blinkMillis = startblinkMillis;
    }

  }
}

void check_answer() {
  int correct = 0;
  for (int index = 0; index < 12; index++)
  {
    if (user_answer[index] != show_answer[index])
    {
      wrong_answer();
      return;
    }
  }
  correct_answer();
  return;
}

void wrong_answer() {
  memset(show_answer, -1, 12);
  memset(user_answer, -1, 12);
  current_set = 0;
  start_game = false;
  num_answer = game_set[current_set];
  stepper.moveTo(0);
  stepper.runToPosition();
  pixel.fill(pixel.Color(255, 0, 0), 0, 12);
  pixel.show();
  delay(500);
  pixel.clear();
  pixel.show();
  pixel.fill(pixel.Color(255, 0, 0), 0, 12);
  pixel.show();
  delay(500);
  pixel.clear();
  pixel.show();
}

void correct_answer() {
  current_set = current_set + 1;
  memset(show_answer, -1, 12);
  memset(user_answer, -1, 12);
  stepper_position = stepper_position + 1500; //Derrick to decide the total amount to reach from bot to top then divide by 5 to replace 1500
  stepper.moveTo(stepper_position);
  stepper.runToPosition();
  if (current_set < 5)
  {
    num_answer = game_set[current_set];
  }
  while (current_set == 5)
  {
    sensor = digitalRead(laser_sensor);
    //turn servo
    if (sensor == HIGH)
    {
      pixel.fill(pixel.Color(0, 255, 0), 0, 12);
      pixel.show();
      delay(500);
      pixel.clear();
      pixel.show();
      delay(500);
    }
  }
}

void time_and_set() {
  //Li Long to add in to display time and current set
}
