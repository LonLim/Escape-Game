//Buttons Pins
#define column1Button A0
#define column2Button A1
#define column3Button A2
#define column4Button A3
#define column5Button A4
#define column6Button A5
#define column7Button A6
#define column8Button A7

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
#define reset 1

//Variables
int position = 0;
int old_correct = 0;
int new_correct = 0;
int current_pos = 0;

int column1Input = 0;
int column2Input = 0;
int column3Input = 0;
int column4Input = 0;
int column5Input = 0;
int column6Input = 0;
int column7Input = 0;
int column8Input = 0;

int column1_index = 8;
int column2_index = 8;
int column3_index = 8;
int column4_index = 8;
int column5_index = 8;
int column6_index = 8;
int column7_index = 8;
int column8_index = 8;

int maze_answer_row = 0;

void setup() {
  pinMode(column1Button, INPUT);
  pinMode(column2Button, INPUT);
  pinMode(column3Button, INPUT);
  pinMode(column4Button, INPUT);
  pinMode(column5Button, INPUT);
  pinMode(column6Button, INPUT);
  pinMode(column7Button, INPUT);
  pinMode(column8Button, INPUT);
  digitalWrite(reset, LOW);
}

void loop() {
  //Read buttons input
  column1Input = analogRead(column1Button);
  column2Input = analogRead(column2Button);
  column3Input = analogRead(column3Button);
  column4Input = analogRead(column4Button);
  column5Input = analogRead(column5Button);
  column6Input = analogRead(column6Button);
  column7Input = analogRead(column7Button);
  column8Input = analogRead(column8Button);

  //Check which button has been pressed
  column1_index = check_button_push(column1Input);
  column2_index = check_button_push(column2Input);
  column3_index = check_button_push(column3Input);
  column4_index = check_button_push(column4Input);
  column5_index = check_button_push(column5Input);
  column6_index = check_button_push(column6Input);
  column7_index = check_button_push(column7Input);
  column8_index = check_button_push(column8Input);

  //Get postion according to button pressed
  if ( column1_index != 8)
  {
    position = column1_index;
  }
  if ( column2_index != 8)
  {
    position = 8 + column2_index;
  }
  if ( column3_index != 8)
  {
    position = 16 + column3_index;
  }
  if ( column4_index != 8)
  {
    position = 24 + column4_index;
  }
  if ( column5_index != 8)
  {
    position = 32 + column5_index;
  }
  if ( column6_index != 8)
  {
    position = 40 + column6_index;
  }
  if ( column7_index != 8)
  {
    position = 48 + column7_index;
  }
  if ( column8_index != 8)
  {
    position = 56 + column8_index;
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
      pixels.setPixelColor(position, pixels.Color(0,150,0)); // Moderately bright green color.
      new_correct  = new_correct + 1;//increase correct to compare with old value
      current_pos = current_pos + 1;//shift index of answer array
    }
  else
    {
      pixels.setPixelColor(position, pixels.Color(150,0,0)); // Moderately bright red color.
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
