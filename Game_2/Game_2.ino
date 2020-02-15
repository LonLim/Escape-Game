#define row1_Buttons A0
#define row2_Buttons A1
#define row3_Buttons A2
#define row4_Buttons A3
#define row5_Buttons A4
#define row6_Buttons A5
#define row7_Buttons A6
#define row8_Buttons A7

int index  = 0;
int row1, row2, row3, row4, row5, row6, row7, row8;

mazeBoard[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
}

void setup() {
  Serial.begin(9600);
  pinMode(row1_Buttons, INPUT);
  pinMode(row2_Buttons, INPUT);
  pinMode(row3_Buttons, INPUT);
  pinMode(row4_Buttons, INPUT);
  pinMode(row5_Buttons, INPUT);
  pinMode(row6_Buttons, INPUT);
  pinMode(row7_Buttons, INPUT);
  pinMode(row8_Buttons, INPUT);
}

void loop() {
  row1 = analogRead(row1_Buttons);
  row2 = analogRead(row2_Buttons);
  row3 = analogRead(row3_Buttons);
  row4 = analogRead(row4_Buttons);
  row5 = analogRead(row5_Buttons);
  row6 = analogRead(row6_Buttons);
  row7 = analogRead(row7_Buttons);
  row8 = analogRead(row8_Buttons);

  if (row1 != 8)
  {
    index = row1;
  }
  if (row2 != 8)
  {
    index = 8 + row2;
  }
  if (row3 != 8)
  {
    index = 16 + row3;
  }
  if (row4 != 8)
  {
    index = 24 + row4;
  }
  if (row5 != 8)
  {
    index = 32 + row5;
  }
  if (row6 != 8)
  {
    index = 40 + row6;
  }
  if (row7 != 8)
  {
    index = 48 + row7;
  }
  if (row8 != 8)
  {
    index = 56 + row8;
  }
}

int check_button_pressed(int analog) { // NOT COMPLETE >> TO BE CONTINUE AFTER GETTING 8 VALUES
  if (analog > 900)
  {
    return 0;
  }
  else if ( 450 < analog < 600)
  {
    return 1;
  }
  else if (300 < analog < 400)
  {
    return 2;
  }
  else if ( 200 < analog < 300)
  {
    return 3;
  }
  else
  {
    return 4;
  }
}
