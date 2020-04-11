#include <Keypad.h>

const byte ROWS = 8;
const byte COLS = 8;
int keys[ROWS][COLS] = {
  {0, 8, 16, 24, 32, 40, 48, 56},
  {1, 9, 17, 25, 33, 41, 49, 57},
  {2, 10, 18, 26, 34, 42, 50, 58},
  {3, 11, 19, 27, 35, 43, 51, 59},
  {4, 12, 20, 28, 36, 44, 52, 60},
  {5, 13, 21, 29, 37, 45, 53, 61},
  {6, 14, 22, 30, 38, 46, 54, 62},
  {7, 15, 23, 31, 39, 47, 55, 63},
};

byte rowPins[ROWS] = {3, 4, 5, 6, 7, 8, 9, 10};
byte colPins[COLS] = {11, 12, 13, 14, 15, 16, 17};

keypad location = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Define neopixel pin and number
#include <Adafruit_NeoPixel.h>
#define NEOPIXELS 2
#define NUMPIXELS 64
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXELS, NEO_GRB + NEO_KHZ800);

//Maze Answer
int maze_array[3][31] = {
  {39, 38, 30, 22, 14, 13, 12, 20, 28, 36, 44, 45, 53, 61, 60, 59, 58, 50, 49, 41, 33, 34, 26, 18, 10, 2, 1, 0, -1, -1, -1},
  {63, 62, 61, 60, 59, 51, 43, 44, 45, 46, 38, 30, 29, 21, 13, 12, 4, 3, 2, 10, 18, 26, 34, 33, 41, 40, -1, -1, -1, -1, -1},
  {7, 6, 5, 4, 3, 2, 1, 9, 17, 25, 26, 34, 35, 36, 28, 20, 21, 22, 30, 38, 46, 45, 53, 52, 60, 59, 58, 50, 49, 41, 40},
};

//Reset pin
#define reset 2

//Variables
int position = 0;
int old_correct = 0;
int new_correct = 0;
int current_pos = 0;

int maze_answer_row = 0;

void setup() {
  digitalWrite(reset, LOW);
}

void loop() {
  if (location.getKeys())
  {
    for (int index = 0; index < LIST_MAX; index ++)//Scan through all buttons
    {
      if ( location.key[0].stateChanged) //Find all button that are pressed
      {
        if (location.key[i].kstate == PRESSED) //Check for new button
        {
          position = location.key[i]
        }
      }
    }
  }

  //Light up the respective neopixel
  new_correct = light_up_maze();
  pixels.show();

  //Check if user has stepped the wrong answer
  if (new_correct < old_correct)
  {
    reset_maze();
  }
  else
  {
    check_maze();
    old_correct = new_correct;
  }
}

//Check button in the series has been pressed
int check_button_push(int input) {
  if (input > 1000)
  {
    return 0;
  }
  else if ((500 < input) && (input < 600))
  {
    return 1;
  }
  else if ((300 < input) && (input < 400))
  {
    return 2;
  }
  else if ((230 < input) && (input < 260))
  {
    return 3;
  }
  else if ((190 < input) && (input < 210))
  {
    return 4;
  }
  else if ((155 < input) && (input < 180))
  {
    return 5;
  }
  else if ((135 < input) && (input < 150))
  {
    return 6;
  }
  else if ((110 < input) && (input < 130))
  {
    return 7;
  }
  else
  {
    return 8;
  }
}

//Light up respective pixel and check if answer is correct
int light_up_maze() {
  if (position == maze_array[maze_answer_row][current_pos])
  {
    pixels.setPixelColor(position, pixels.Color(0, 150, 0)); // Moderately bright green color.
    new_correct  = new_correct + 1;//increase correct to compare with old value
    current_pos = current_pos + 1;//shift index of answer array
  }
  else
  {
    pixels.setPixelColor(position, pixels.Color(150, 0, 0)); // Moderately bright red color.
    new_correct = new_correct - 1;//decrease correct to compare with old value
  }
  return new_correct;
}

//Check if maze has been completed
void check_maze() {
  switch (maze_answer_row) //check with maze answer currently on
  {
    case 0:
      while (new_correct == 28) //force freeze
      {
        pixels.fill(pixels.Color(0, 150, 0), 0, 64);
        pixels.show();
      }
    case 1:
      while (new_correct == 26) //force freeze
      {
        pixels.fill(pixels.Color(0, 150, 0), 0, 64);
        pixels.show();
      }
    case 2:
      while (new_correct == 31) //force freeze
      {
        pixels.fill(pixels.Color(0, 150, 0), 0, 64);
        pixels.show();
      }
  }
}

//Reset maze if user has stepped wrong
void reset_maze() {
  pixels.clear();
  pixels.show();
  digitalWrite(reset, HIGH);
  old_correct = 0;
  new_correct = 0;
  current_pos = 0;
  maze_answer_row = maze_answer_row + 1;//change maze answer
  if (maze_answer_row == 3)//reset if over boundary
  {
    maze_answer_row = 0;
  }
}
