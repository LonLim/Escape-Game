#include <Adafruit_NeoPixel.h>
#define NUM_PIXELS 14
#define PIXEL_PIN 13
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

#define x_direction A0
int x_value = 0;

#define red_button 4
#define blue_button 5
#define green_button 6
int red_value = 1;
int blue_value = 1;
int green_value = 1;

uint32_t red = pixel.Color(255, 0, 0);
uint32_t green = pixel.Color(0, 255, 0);
uint32_t blue = pixel.Color(0, 0, 255);
uint32_t yellow = pixel.Color(255, 255, 0);
uint32_t cyan = pixel.Color(0, 255, 255);
uint32_t purple = pixel.Color(250, 0, 255);
uint32_t white = pixel.Color(255, 255, 255);
uint32_t color_array[] = {red, green, blue, yellow, purple, cyan, white};

int show_answer[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int user_answer[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int game_set[5] = {6, 7, 8, 10, 12};

int num_answer;
int current_set = 0;
int pos = 0;

//Delays
unsigned long startPressMillis;
const unsigned pressMillis = 15000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixel.begin();
  num_answer = game_set[current_set];
}

void loop() {
  // put your main code here, to run repeatedly:
  get_color();
  show_color();
  startPressMillis = millis();
  while (startPressMillis != pressMillis)
  {
    user_input();
  }
  check_answer();
  startPressMillis = 0;
}

void get_color() {
  for (int index = 0; index < 12; index++)
  {
    if (index < num_answer)
    {
      int color = random(0, 6);
      show_answer[index] = color_array[color];
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
      pixel.setPixelColor(index, show_answer[index]);
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
    change_answer();
  }
  if (blue_value == '0')
  {
    change_answer();
  }
  if (green_button == '0')
  {
    change_answer();
  }
}

int change_answer() { //Li Long to input swtich case
  
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
  num_answer = game_set[current_set];
  //Add show all red with blink
}

void correct_answer() {
  current_set = current_set + 1;
  memset(show_answer, -1, 12);
  memset(user_answer, -1, 12);
  if (current_set < 5)
  {
    num_answer = game_set[current_set];
  }
  while (current_set == 5)
  {
    //Add show all green
    //On laser and detect LDR
  }
}
