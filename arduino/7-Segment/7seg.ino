 /*
 * Original code from https://github.com/avishorp/TM1637
 * Modified for Robojax video on Oct 28, 2018 at 15:05
 * This is Arduino sketch to use two more TM1637 seven-segment LED displays
 * 
 * Watch video instruciton for this code:https://youtu.be/27KjMfPH1dk
 * 
 * by Ahmad Shamshiri, in Ajax, Ontario, Canada
 * 
 *  display2.showNumberDec(23, true, 2,1);
 *  showNumberDec(arg1, arg2, arg3, arg4);
 *  arg1 is the numbr to be displayed
 *  arg2 can be 'true' or 'false' and if true it fills empty spot with data[]
 *  arg4 position of star showing  number on the display can be either 0, 1, 2 or 3
 */
#include <Arduino.h>
#include <TM1637Display.h>

// Module 1 connection pins (Digital Pins)
#define CLK1 40
#define DIO1 32

// Module 2 connection pins (Digital Pins)
#define CLK2 44
#define DIO2 34

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   5000


TM1637Display display1(44, 32);// define dispaly 1 object
TM1637Display display2(44, 30);// define dispaly 1 object
TM1637Display display3(44, 34);// define dispaly 1 object
   uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };  // all segments clear    
   
void setup()
{
  // Robojax.com two or more TM1637 Display 20181029  
  display1.setBrightness(0x0f);// set brightness of dispaly 1
  display2.setBrightness(0x0f);// set brightness of dispaly 1  
  display3.setBrightness(0x0f);// set brightness of dispaly 1  
 
  display1.setSegments(data);// fill display 1 with whatever data[] array has
  display2.setSegments(data);// // fill display 2 with whatever data[] array has  
  display3.setSegments(data);// // fill display 2 with whatever data[] array has  
// Robojax.com two or more TM1637 Display 20181029  
}

void loop()
{
 // Robojax.com two or more TM1637 Display 20181029
/////////////////////////////////////////////////
  display1.setSegments(data); // fill(clear) display with data[] array    
  display1.showNumberDec(23, false, 2,0);

  display2.setSegments(data);// fill(clear) display with data[] array
  display2.showNumberDec(34, false, 2,0);
  
  display3.setSegments(data);// fill(clear) display with data[] array
  display3.showNumberDec(12, false, 2,0);

  
  delay(TEST_DELAY);// wait for TEST_DELAY miliseconds
  
/////////////////////////////////////////////////
  display1.setSegments(data); // fill(clear) display with data[] array    
  display1.showNumberDec(23, false, 2,1);

  display2.setSegments(data);// fill(clear) display with data[] array
  display2.showNumberDec(34, false, 2,1);
  
  display3.setSegments(data);// fill(clear) display with data[] array
  display3.showNumberDec(12, false, 2,1);

  delay(TEST_DELAY);// wait for TEST_DELAY miliseconds
/////////////////////////////////////////////////
  display1.setSegments(data); // fill(clear) display with data[] array    
  display1.showNumberDec(23, false, 2,2);

  display2.setSegments(data);// fill(clear) display with data[] array
  display2.showNumberDec(34, false, 2,2);

  display3.setSegments(data);// fill(clear) display with data[] array
  display3.showNumberDec(12, false, 2,2);
  delay(TEST_DELAY);// wait for TEST_DELAY miliseconds
/////////////////////////////////////////////////
  display1.setSegments(data); // fill(clear) display with data[] array    
  display1.showNumberDec(23, false, 2,3);

  display2.setSegments(data);// fill(clear) display with data[] array
  display2.showNumberDec(34, false, 2,3);
  
  display3.setSegments(data);// fill(clear) display with data[] array
  display3.showNumberDec(12, false, 2,3);

  delay(TEST_DELAY);// wait for TEST_DELAY miliseconds    
/////////////////////////////////////////////////
  display1.setSegments(data);// fill(clear) display with data[] array
  display1.showNumberDec(741);// display 1

  display2.setSegments(data);// fill(clear) display with data[] array  
  display2.showNumberDec(1562);// display 2

  display3.setSegments(data);// fill(clear) display with data[] array
  display3.showNumberDec(12, false, 2,3);
  
  delay(TEST_DELAY);// wait for TEST_DELAY miliseconds

// Robojax.com two or more TM1637 Display 20181029 
/////////////////////////////////////////////////
   display1.setSegments(data);// fill(clear) display 1 with data[] array
   display2.setSegments(data);// fill(clear) display 2 with data[] array  
   display3.setSegments(data);// fill(clear) display 2 with data[] array    
  for(int i=0; i<=1273; i++)
  {
    display1.showNumberDec(i);// display from 0 to 1273 to diasplay 1
    display2.showNumberDec(i);// display from 0 to 1273 to diasplay 2    
    display3.showNumberDec(i);// display from 0 to 1273 to diasplay 2    
  }
  delay(TEST_DELAY);// wait for TEST_DELAY miliseconds


// Robojax.com two or more TM1637 Display 20181029
  
}// loop end
 
