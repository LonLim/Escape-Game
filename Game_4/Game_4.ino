//NeoPixels
#include <Adafruit_NeoPixel.h>
#define NUM_PIXELS 14
#define PIXEL_PIN 3
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

//Stepper Motor 1
#include <AccelStepper.h>
#define motor1Pin1  4      // IN1 on the ULN2003 driver
#define motor1Pin2  5      // IN2 on the ULN2003 driver
#define motor1Pin3  6     // IN3 on the ULN2003 driver
#define motor1Pin4  7     // IN4 on the ULN2003 driver
#define Motor1InterfaceType 8
AccelStepper stepper1 = AccelStepper(Motor1InterfaceType, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
int stepper1_position = 0;

//Stepper Motor 2
#define motor2Pin1  9      // IN1 on the ULN2003 driver
#define motor2Pin2  10      // IN2 on the ULN2003 driver
#define motor2Pin3  11   // IN3 on the ULN2003 driver
#define motor2Pin4  12     // IN4 on the ULN2003 driver
#define Motor2InterfaceType 13
AccelStepper stepper2 = AccelStepper(Motor2InterfaceType, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);
int stepper2_position = 6000;

//Analog Joystick
#define x_direction A0
int x_value = 0;

//Red, Blue, Green Button
#define red_button 13
#define blue_button 14
#define green_button 15
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
#define start_button 16
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
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000); // Set the maximum steps per second
  stepper1.setAcceleration(200); // Set the maximum acceleration in steps per second^2
  stepper2.setMaxSpeed(1000); // Set the maximum steps per second
  stepper2.setAcceleration(200); // Set the maximum acceleration in steps per second^2
  pixel.begin();
  startblinkMillis = millis();
  num_answer = game_set[current_set];
}

void loop() {
  //wait for start button pressed
  if (digitalRead(start_button == '0'))
  {
    start_game = true;
  }
  while (start_game == true)
  {
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
      //get random number
      show_answer[index] = random(0, 6);
    }
    else
    {
      //close rest of pixel
      show_answer[index] = -1;
    }
  }
}

void show_color() {
  for (int index = 0; index < 12; index++)
  {
    if (show_answer[index] != -1)
    {
      //display all color
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
  //check joystick movement
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
  //read all 3 color buttons
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

int change_answer(int currentColor, int button) {
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
    if (user_answer[pos] != -1)
    {
      pixel.setPixelColor(index, color_array[user_answer[index]]);
      pixel.show();
    }
    else
    {
      pixel.setPixelColor(pos, pixel.Color(0, 0, 0));
    }
  }
  if (startblinkMillis - blinkMillis >= 500)
  {
    //check current status of blink
    if (current_status == false)
    {
      current_status = true;
      blinkMillis = startblinkMillis;
      if (user_answer[pos] != -1)
      {
        pixel.setPixelColor(pos, color_array[user_answer[pos]]);

      }
      else
      {
        pixel.setPixelColor(pos, pixel.Color(0, 0, 0));
      }
      pixel.show();
    }
    else
    {
      pixel.setPixelColor(pos, pixel.Color(0, 0, 0));
      current_status = false;
      blinkMillis = startblinkMillis;
      pixel.show();
    }
  }
}

void check_answer() {
  int correct = 0;
  for (int index = 0; index < 12; index++)
  {
    //check answer
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
  //Reset all arrays
  memset(show_answer, -1, 12);
  memset(user_answer, -1, 12);
  current_set = 0;
  //Reset start game to wait for start button press
  start_game = false;
  num_answer = game_set[current_set];
  //Reset both stepper to original position
  stepper1.moveTo(0);
  stepper1.runToPosition();
  stepper2.moveTo(6000);
  stepper2.runToPosition();
  //Blink Red
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
  //increase set and reset all array
  current_set = current_set + 1;
  memset(show_answer, -1, 12);
  memset(user_answer, -1, 12);
  //Stepper 1 motor in clockwise movement
  stepper1_position = stepper1_position + 1500;
  stepper1.moveTo(stepper1_position);
  stepper1.runToPosition();
  //Steppper 2 motor in anti-clockwise movement
  stepper2_position = stepper2_position - 1500;
  stepper2.moveTo(stepper2_position);
  stepper2.runToPosition();
  //Check if finish 4 set
  if (current_set < 4)
  {
    num_answer = game_set[current_set];
  }
  //Force freeze
  while (current_set == 4)
  {
    //Turn Green light and blink
    pixel.fill(pixel.Color(0, 255, 0), 0, 12);
    pixel.show();
    delay(500);
    pixel.clear();
    pixel.show();
    delay(500);
  }
}
