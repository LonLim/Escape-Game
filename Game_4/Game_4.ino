#include <Adafruit_NeoPixel.h>
#define NUM_PIXELS 14
#define PIXEL_PIN 13
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int color_array[7] = {
  (255, 0, 0), //Red
  (0, 255, 0), //Green
  (0, 0, 255), //Blue
  (255, 255, 0), //Yellow
  (255, 0, 255), //Purple
  (0, 255, 255), //Light Blue
  (255, 255, 255), //White
};

int show_answer[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int num_answer = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixel.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

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
