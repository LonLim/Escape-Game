int playerPosition = 0;

int location[64];

//Pins & Variables for analog joystick
#define analog_x A0
#define analog_y A1
#define analog_button 52
int x_value = 0;
int y_value = 0;
int swtich = 0;

void setup() {
  // open the serial port:
  Serial.begin(9600);
  digitalWrite(analog_button, HIGH);
  pinMode(analog_x, INPUT);
  pinMode(analog_y, INPUT);
  updateLocation(playerPosition);
}

void loop() {
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

void updateLocation (int playerPosition)  { // Update the location of the pixel
  //memset(location,0,sizeof(location));
  //easiest way to reset all array to zero
  initLocation(playerPosition);
  if (location[playerPosition] != 2) 
  {
    location[playerPosition] = 1;
  }
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++) 
      {
        Serial.print(location[j+8*i]);
        Serial.print("  ");
      }
    Serial.println("");
  }
  Serial.println("----------------------------------------------");
  Serial.println(playerPosition);
  delay(500);
}

int checkSideBountary(int playerPosition) { // check if position has moved out of side boundary
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

int checkBottomBountary(int playerPosition) { // check if position has moved out of bottom boundary
  if (playerPosition % 8 == 0)
  {
    playerPosition = playerPosition - 8;
  }
  return playerPosition;
}

int checkTopBountary(int playerPosition) { // check if position has moved out of top boundary
  if ((playerPosition + 1) % 8 == 0)
  {
    playerPosition = playerPosition + 8;
  }
  return playerPosition;
}

void initLocation(int playerPosition) { // init all pixel and change to its relevant number accordingly
   for (int position = 0; position < 64; position++)
   {
      if(location[position] != 2)
      {
        location[position] = 0;
      }
      if(location[position] == 2 || location[position] == 3)
      {
        location[position] = 2;
      }
      if(location[position] == 2 && position == playerPosition)
      {
        location[position = 3;
      }
   }
}
