#include <TM1637Display.h> 
#define CLK 14 //can be any digital pin 
#define DIO1 1 //can be any digital pin
#define DIO2 2 //can be any digital pin 
#define DIO3 3 //can be any digital pin 
#define DIO4 4 //can be any digital pin
#define DIO5 5 //can be any digital pin
#define DIO6 6 //can be any digital pin 
#define DIO7 7 //can be any digital pin 
#define DIO8 8 //can be any digital pin 
#define DIO9 9 //can be any digital pin
#define DIO10 10 //can be any digital pin 
#define DIO11 11 //can be any digital pin 
#define DIO12 12 //can be any digital pin  

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   5000
 
TM1637Display display1(9, 1); 
TM1637Display display2(9, 2); 
TM1637Display display3(9, 3);
TM1637Display display4(9, 4);
TM1637Display display5(9, 5); 
TM1637Display display6(9, 6); 
TM1637Display display7(9, 7);
TM1637Display display8(9, 8); 
TM1637Display display9(9, 9); 
TM1637Display display10(9, 10); 
TM1637Display display11(9, 11);
TM1637Display display12(9, 12);  
 
uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };  // all segments clear    

int clue_array[3][28] = {
  {11, 4, 2, 1, 111, 4, 112, 3, 3311, 0, 2214, 0, 1, 4, 13, 4, 52, 4, 1, 4, 51, 4, 13, 4, 4, 4, 1, 4},
  {1, 0, 1, 0, 111, 4, 22, 2, 3212, 0, 1415, 0, 1, 4, 2, 4, 5, 4, 13, 4, 211, 4, 311, 4, 31, 4, 1, 4},
  {2, 4, 1, 0, 11, 4, 32, 2, 7131, 0, 1223, 0, 1, 4, 42, 4, 122, 4, 111, 4, 132, 4, 112, 4, 14, 4, 1, 4},
};

#define reset_switch 13
int row = 0;

void setup() {
  // put your setup code here, to run once:
  display1.setBrightness(0x0f);// set brightness of dispaly 1
  display2.setBrightness(0x0f);// set brightness of dispaly 1  
  display3.setBrightness(0x0f);// set brightness of dispaly 1  
  display4.setBrightness(0x0f);// set brightness of dispaly 1 
  display5.setBrightness(0x0f);// set brightness of dispaly 1
  display6.setBrightness(0x0f);// set brightness of dispaly 1  
  display7.setBrightness(0x0f);// set brightness of dispaly 1  
  display8.setBrightness(0x0f);// set brightness of dispaly 1  
  display9.setBrightness(0x0f);// set brightness of dispaly 1
  display10.setBrightness(0x0f);// set brightness of dispaly 1  
  display11.setBrightness(0x0f);// set brightness of dispaly 1  
  display12.setBrightness(0x0f);// set brightness of dispaly 1  
 

  display1.setSegments(data);// fill display 1 with whatever data[] clue_array has
  display2.setSegments(data);// fill display 2 with whatever data[] clue_array has  
  display3.setSegments(data);// fill display 3 with whatever data[] clue_array has
  display4.setSegments(data);// fill display 4 with whatever data[] clue_array has
  display5.setSegments(data);// fill display 5 with whatever data[] clue_array has
  display6.setSegments(data);// fill display 6 with whatever data[] clue_array has  
  display7.setSegments(data);// fill display 7 with whatever data[] clue_array has
  display8.setSegments(data);// fill display 8 with whatever data[] clue_array has
  display9.setSegments(data);// fill display 9 with whatever data[] clue_array has
  display10.setSegments(data);// fill display 10 with whatever data[] clue_array has  
  display11.setSegments(data);// fill display 11 with whatever data[] clue_array has
  display12.setSegments(data);// fill display 12 with whatever data[] clue_array has  

  pinMode(reset_switch, INPUT);
  row = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  display_clue(row);
  if (digitalRead(reset_switch) == HIGH)
  {
    row = row + 1;
    if (row == 3)
    {
      row = 0;
    }
  }
}

void display_clue(int row) {
  display1.setSegments(data);// fill(clear) display with data[] clue_array
  display1.showNumberDec(clue_array[row][0], 0, clue_array[row][1]);// display 1

  display2.setSegments(data);// fill(clear) display with data[] clue_array  
  display2.showNumberDec(clue_array[row][2], 0, clue_array[row][3]);// display 2

  display3.setSegments(data);// fill(clear) display with data[] clue_array
  display3.showNumberDec(clue_array[row][4], 0, clue_array[row][5]);// display 3

  display4.setSegments(data);// fill(clear) display with data[] clue_array
  display4.showNumberDec(clue_array[row][6], 0, clue_array[row][7]);// display 4
  
  display5.setSegments(data);// fill(clear) display with data[] clue_array
  display5.showNumberDec(clue_array[row][8], 0, clue_array[row][9]);// display 5

  display6.setSegments(data);// fill(clear) display with data[] clue_array  
  display6.showNumberDec(clue_array[row][10], 0, clue_array[row][11]);// display 6

  display7.setSegments(data);// fill(clear) display with data[] clue_array
  display7.showNumberDec(clue_array[row][12], 0, clue_array[row][13]);// display 7

  display8.setSegments(data);// fill(clear) display with data[] clue_array
  display8.showNumberDec(clue_array[row][14], 0, clue_array[row][15]);// display 8
  
  display9.setSegments(data);// fill(clear) display with data[] clue_array
  display9.showNumberDec(clue_array[row][16], 0, clue_array[row][17]);// display 9

  display10.setSegments(data);// fill(clear) display with data[] clue_array  
  display10.showNumberDec(clue_array[row][18], 0, clue_array[row][19]);// display 10

  display11.setSegments(data);// fill(clear) display with data[] clue_array
  display11.showNumberDec(clue_array[row][20], 0, clue_array[row][21]);// display 11

  display12.setSegments(data);// fill(clear) display with data[] clue_array
  display12.showNumberDec(clue_array[row][22], 0, clue_array[row][23]);// display 12
}
