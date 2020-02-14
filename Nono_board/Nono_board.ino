#include <Adafruit_NeoPixel.h>
#define analog_button 0
#define analog_x A0
#define analog_y A1

int index = 0;

int row = 0;
int col = 0;

#define NEOPIXEL 2
#define NUMPIXELS 64
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL, NEO_GRB + NEO_KHZ800);

int board[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};

void setup() {
  pinMode(analog_button, INPUT);
  pinMode(analog_x, INPUT);
  pinMode(analog_y, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (analog_y > 600)
  {
    index += 1;
    index = check_border(index);
  }
  if (analog_y < 450)
  {
    index -= 1;
    index = check_border(index);
  }
  if (analog_x > 600)
  {
    index += 8;
    index = check_border(index);
  }
  if (analog_x < 450)
  {
    index -=8;
    index = check_border(index);
  }

  if (analog_button == 1)
  {
    row, col = get_array(index);
    board[row][col] = ~board[row][col];
  }
}

int check_border(int index) {
  if ((index + 1) % 8 == 0)
  {
    index +=8;
  }
  if (index % 8 == 0)
  {
    index -=8;
  }
  if (index < 0)
  {
    index +=64;
  }
  if (index > 63 == 0)
  {
    index -=64;
  }
  return index;
}

int get_array(int index) {
  row = int(index / 8);
  col = index % 8;
  return row, col;
}
