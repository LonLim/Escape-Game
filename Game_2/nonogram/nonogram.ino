//Define neopixel pin and number
#include <Adafruit_NeoPixel.h>
#define NEOPIXEL1 2
#define NUMPIXELS 64
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL1, NEO_GRB + NEO_KHZ800);

//Variables
int playerPosition = 0;
int location[64];

//Pins & Variables for analog joystick
#define analog_x A0
#define analog_y A1
#define analog_button 11


//Reset pin
#define reset 12

//Initialize value for joystick
int x_value = 0;
int y_value = 0;
int swtich = 0;

//Variable and array for Clue
int clue_row = 0;
int clue_array[3][28] = {
  {11, 4, 2, 1, 111, 4, 112, 3, 3311, 0, 2214, 0, 1, 4, 13, 4, 52, 4, 1, 4, 51, 4, 13, 4, 4, 4, 1, 4},
  {1, 0, 1, 0, 111, 4, 22, 2, 3212, 0, 1415, 0, 1, 4, 2, 4, 5, 4, 13, 4, 211, 4, 311, 4, 31, 4, 1, 4},
  {2, 4, 1, 0, 11, 4, 32, 2, 7131, 0, 1223, 0, 1, 4, 42, 4, 122, 4, 111, 4, 132, 4, 112, 4, 14, 4, 1, 4},
};

//Define for all Display
#include <TM1637Display.h> 
#define CLK 10
#define DIO0 0
#define DIO1 1
#define DIO2 2
#define DIO3 3
#define DIO4 4
#define DIO5 5
#define DIO6 6
#define DIO7 7
#define DIO8 8
#define DIO9 9
#define AIO2 A2
#define AIO3 A3
#define AIO4 A4
#define AIO5 A5
 
TM1637Display display1(CLK, DIO0); 
TM1637Display display2(CLK, DIO1); 
TM1637Display display3(CLK, DIO2);
TM1637Display display4(CLK, DIO3);
TM1637Display display5(CLK, DIO4); 
TM1637Display display6(CLK, DIO5); 
TM1637Display display7(CLK, DIO6);
TM1637Display display8(CLK, DIO7); 
TM1637Display display9(CLK, DIO8); 
TM1637Display display10(CLK, DIO9); 
TM1637Display display11(CLK, AIO2);
TM1637Display display12(CLK, AIO3);
TM1637Display display13(CLK, AIO4);
TM1637Display display14(CLK, AIO5);

uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };  // all segments clear

void setup() {
  Serial.begin(9600);
  pixels.begin();
  digitalWrite(analog_button, HIGH);
  pinMode(analog_x, INPUT);
  pinMode(analog_y, INPUT);
  updateLocation(playerPosition);
  pinMode(reset, INPUT);

  //Set Brightness for all display
  display1.setBrightness(0x0f);
  display2.setBrightness(0x0f);
  display3.setBrightness(0x0f);
  display4.setBrightness(0x0f);
  display5.setBrightness(0x0f);
  display6.setBrightness(0x0f);
  display7.setBrightness(0x0f);
  display8.setBrightness(0x0f);
  display9.setBrightness(0x0f);
  display10.setBrightness(0x0f);
  display11.setBrightness(0x0f);  
  display12.setBrightness(0x0f); 
  display13.setBrightness(0x0f);
  display14.setBrightness(0x0f);
  
  //Fill all display with empty data
  display1.setSegments(data);
  display2.setSegments(data);  
  display3.setSegments(data);
  display4.setSegments(data);
  display5.setSegments(data);
  display6.setSegments(data);
  display7.setSegments(data);
  display8.setSegments(data);
  display9.setSegments(data);
  display10.setSegments(data);  
  display11.setSegments(data);
  display12.setSegments(data);
  display13.setSegments(data);
  display14.setSegments(data);
}

void loop() {
  //check if reset pin is HIGH
  checkReset();

  //Display the clue in 7-Segments
  displayClue();
  
  // check for incoming data from joystick
  x_value = analogRead(analog_x);
  y_value = analogRead(analog_y);
  swtich = digitalRead(analog_button);
  if (y_value < 400)
  {
    playerPosition = playerPosition - 1;
    playerPosition = checkTopBountary(playerPosition);
    updateLocation(playerPosition);
  }
  else if (y_value > 600)
  {
    playerPosition = playerPosition + 1;
    playerPosition = checkBottomBountary(playerPosition);
    updateLocation(playerPosition);
  }
  else if (x_value < 400)
  {
    playerPosition = playerPosition - 8;
    playerPosition = checkSideBountary(playerPosition);
    updateLocation(playerPosition);
  }
  else if (x_value > 600)
  {
    playerPosition = playerPosition + 8;
    playerPosition = checkSideBountary(playerPosition);
    updateLocation(playerPosition);
  }
  else if (swtich == LOW)
  {
    if(location[playerPosition] == 1)
    {
      location[playerPosition] = 2;
    }
    else
    {
      location[playerPosition] = 0;
    }
    updateLocation(playerPosition);
  }
}

// Update the location of the pixel
void updateLocation (int playerPosition)  { 
  //memset(location,0,sizeof(location));
  //easiest way to reset all array to zero
  initLocation(playerPosition);
  if (location[playerPosition] != 2) 
  {
    location[playerPosition] = 1;
  }
  //For Debugging
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
      {
        Serial.print(location[row+8*col]);
        Serial.print("  ");
      }
    Serial.println("");
  }
  Serial.println("----------------------------------------------");
  Serial.println(playerPosition);
  delay(500);
  setLEDColor();
}

//Prevent user from going over the side boundary of the board
int checkSideBountary(int playerPosition) {
  if (playerPosition < 0)
  {
    playerPosition = playerPosition + 64;
  }
  else if (playerPosition > 63)
  {
    playerPosition = playerPosition - 64;
  }
  return playerPosition;
}

//Prevent user from going over the bottom boundary of the board
int checkBottomBountary(int playerPosition) {
  if (playerPosition % 8 == 0)
  {
    playerPosition = playerPosition - 8;
  }
  return playerPosition;
}

//Prevent user from going over the top boundary of the board
int checkTopBountary(int playerPosition) {
  if ((playerPosition + 1) % 8 == 0)
  {
    playerPosition = playerPosition + 8;
  }
  return playerPosition;
}

//Init all pixel and change to its relevant number accordingly
void initLocation(int playerPosition) { 
   for (int position = 0; position < 64; position++)
   {
      if(location[position] == 3)
      {
        location[position] = 2;
      }
      if(location[position] != 2)
      {
        location[position] = 0;
      }
      if(location[position] == 2 && position == playerPosition)
      {
        location[position] = 3;
      }
   }
}

//Update location to the pixel
void setLEDColor()  {    
   for(int position = 0; position < 64; position++){ 
      switch (location[position]){
        case 1:
          pixels.setPixelColor(position, pixels.Color(150,0,0)); // Moderately bright red color.
          break;
        case 2:
          pixels.setPixelColor(position, pixels.Color(0,150,0)); // Moderately bright green color.
          break;
        case 3:
          pixels.setPixelColor(position, pixels.Color(0,0,150)); // Moderately bright blue color.
          break;
        default:
          pixels.setPixelColor(position, pixels.Color(0,0,0)); // Off the pixel
       break;
    }
    pixels.show();
  }
}

//Check if reset pin is HIGH
void checkReset() {
  if ( digitalRead(reset) == HIGH)
  {
    clue_row = clue_row + 1;
    if (clue_row = 3)
    {
      clue_row = 0;
    }
  }
}

//Display clue at 7 segments
void displayClue() {
  display1.setSegments(data);// fill(clear) display with data[] clue_array
  display1.showNumberDec(clue_array[clue_row][0], 0, clue_array[clue_row][1]);// display 1

  display2.setSegments(data);// fill(clear) display with data[] clue_array  
  display2.showNumberDec(clue_array[clue_row][2], 0, clue_array[clue_row][3]);// display 2

  display3.setSegments(data);// fill(clear) display with data[] clue_array
  display3.showNumberDec(clue_array[clue_row][4], 0, clue_array[clue_row][5]);// display 3

  display4.setSegments(data);// fill(clear) display with data[] clue_array
  display4.showNumberDec(clue_array[clue_row][6], 0, clue_array[clue_row][7]);// display 4
  
  display5.setSegments(data);// fill(clear) display with data[] clue_array
  display5.showNumberDec(clue_array[clue_row][8], 0, clue_array[clue_row][9]);// display 5

  display6.setSegments(data);// fill(clear) display with data[] clue_array  
  display6.showNumberDec(clue_array[clue_row][10], 0, clue_array[clue_row][11]);// display 6

  display7.setSegments(data);// fill(clear) display with data[] clue_array
  display7.showNumberDec(clue_array[clue_row][12], 0, clue_array[clue_row][13]);// display 7

  display8.setSegments(data);// fill(clear) display with data[] clue_array
  display8.showNumberDec(clue_array[clue_row][14], 0, clue_array[clue_row][15]);// display 8
  
  display9.setSegments(data);// fill(clear) display with data[] clue_array
  display9.showNumberDec(clue_array[clue_row][16], 0, clue_array[clue_row][17]);// display 9

  display10.setSegments(data);// fill(clear) display with data[] clue_array  
  display10.showNumberDec(clue_array[clue_row][18], 0, clue_array[clue_row][19]);// display 10

  display11.setSegments(data);// fill(clear) display with data[] clue_array
  display11.showNumberDec(clue_array[clue_row][20], 0, clue_array[clue_row][21]);// display 11

  display12.setSegments(data);// fill(clear) display with data[] clue_array
  display12.showNumberDec(clue_array[clue_row][22], 0, clue_array[clue_row][23]);// display 12
  
  display13.setSegments(data);// fill(clear) display with data[] clue_array
  display13.showNumberDec(clue_array[clue_row][24], 0, clue_array[clue_row][25]);// display 13
  
  display14.setSegments(data);// fill(clear) display with data[] clue_array
  display14.showNumberDec(clue_array[clue_row][26], 0, clue_array[clue_row][27]);// display 14
}
