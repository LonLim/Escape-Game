//Libraries
#include <Keypad.h>
#include <Servo.h>

//LED pins
#define GreenLED 13
#define RedLED 12

//Variables
unsigned long time;
Servo myservo;
char password[] = { '9', '4', '5', '8'};
char password_keyed [5];
int index = 0;
int match = 0;

//define the symbols on the buttons of the keypads
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

//initialize an instance of class NewKeypad
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  //Serial.begin(9600);
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  myservo.attach(10);
}

void loop() {
  //Get keypad pressed
  char customKey = customKeypad.getKey();//get character from kepad
  if (customKey) { //check whether the user entered a key in the keypad
    password_keyed[index] = customKey;
    if (index < 4) {
      index++;
    }

    else if (password_keyed[index] != '*') // check if last key was '*', else shift left to take last 4 entry
    {
      password_keyed[index] = customKey;
      for (int i = 0; i < 4; i++)
      {
        password_keyed[i] = password_keyed[i + 1];
      }
    }
  }

  if (millis() - time > 3000) {//For turning off Red LED
    digitalWrite(RedLED, LOW);
  }

  if (customKey == '*') { // compare password if '*' was pressed
    for (int key = 0; key < 4; key++)
    {
      if (password_keyed[key] == password[key])
      {
        match++;
      }
      else if (password_keyed[key] == '#') {
        match--; //password to reset everything
      }
    }

    if (match == 4) {
      digitalWrite(GreenLED, HIGH);
      myservo.write(90);
    }
    else if (match == -4) { //reset everything and lock the box.
      myservo.write(180);
      digitalWrite(GreenLED, LOW);
      digitalWrite(RedLED, LOW);
    }
    else
    {
      digitalWrite(RedLED, HIGH);
      time = millis();
    }
    match = 0;
    index = 0;
  }
}
