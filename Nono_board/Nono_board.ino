#include <Adafruit_NeoPixel.h>
#include <TM1637Display.h>
#define analog_button 0
#define analog_x A0
#define analog_y A1
#define reset_button 4

#define CLK 29
#define DIO1 30
TM1637Display firstDisplay(CLK, DIO1);
#define DIO2 32
TM1637Display secondDisplay(CLK, DIO2);
#define DIO3 34
TM1637Display thirdDisplay(CLK, DIO3);
#define DIO4 36
TM1637Display fourthDisplay(CLK, DIO4);
#define DIO5 38
TM1637Display fifthDisplay(CLK, DIO5);
#define DIO6 40
TM1637Display sixthDisplay(CLK, DIO6);
#define DIO7 42
TM1637Display seventhDisplay(CLK, DIO7);
#define DIO8 44
TM1637Display eighthDisplay(CLK, DIO8);
#define DIO9 46
TM1637Display ninethDisplay(CLK, DIO9);
#define DIO10 48
TM1637Display tenthDisplay(CLK, DIO10);
#define DIO11 50
TM1637Display eleventhDisplay(CLK, DIO11);
#define DIO12 52
TM1637Display twelvethDisplay(CLK, DIO12);

int index = 0;

int row = 0;
int col = 0;

int nonogram_row = 0;

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

int all_nonogram[3][12] = {
  {0x73, 0x86, 0x3f, 0x00, 0x73, 0x86, 0x3f, 0x00, 0x73, 0x86, 0x3f, 0x00},
  {0x73, 0x86, 0x3f, 0x00, 0x73, 0x86, 0x3f, 0x00, 0x73, 0x86, 0x3f, 0x00},
  {0x73, 0x86, 0x3f, 0x00, 0x73, 0x86, 0x3f, 0x00, 0x73, 0x86, 0x3f, 0x00},
};

void setup() {
  pinMode(analog_button, INPUT);
  pinMode(analog_x, INPUT);
  pinMode(analog_y, INPUT);
  pinMode(reset_button, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (analog_y > 600)
  {
    index += 1;
    index = check_row_border(index);
  }
  if (analog_y < 450)
  {
    index -= 1;
    index = check_row_border(index);
  }
  if (analog_x > 600)
  {
    index += 8;
    index = check_column_border(index);
  }
  if (analog_x < 450)
  {
    index -=8;
    index = check_column_border(index);
  }

  if (analog_button == 1)
  {
    row, col = get_array(index);
    board[row][col] = ~board[row][col];
  }
  check_reset();
  display_all_4_in_1_digit();
}

int check_row_border(int index) {
  if ((index + 1) % 8 == 0)
  {
    index +=8;
  }
  if (index % 8 == 0)
  {
    index -=8;
  }
  return index;
}

int check_column_border(int index) {
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

void check_reset () {
  if (digitalRead(reset_button) == HIGH)
  {
    nonogram_row += 1;
    if (nonogram_row == 4)
    {
      nonogram_row = 0;
    }
  }
}

void display_all_4_in_1_digit() {
  firstDisplay.setSegments(all_nonogram[nonogram_row][0]);
  secondDisplay.setSegments(all_nonogram[nonogram_row][1]);
  thirdDisplay.setSegments(all_nonogram[nonogram_row][2]);
  fourthDisplay.setSegments(all_nonogram[nonogram_row][3]);
  fifthDisplay.setSegments(all_nonogram[nonogram_row][4]);
  sixthDisplay.setSegments(all_nonogram[nonogram_row][5]);
  seventhDisplay.setSegments(all_nonogram[nonogram_row][6]);
  eighthDisplay.setSegments(all_nonogram[nonogram_row][7]);
  ninethDisplay.setSegments(all_nonogram[nonogram_row][8]);
  tenthDisplay.setSegments(all_nonogram[nonogram_row][9]);
  eleventhDisplay.setSegments(all_nonogram[nonogram_row][10]);
  twelvethDisplay.setSegments(all_nonogram[nonogram_row][11]);
}
