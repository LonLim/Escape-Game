int x = 0;
int location[64];

void setup() {
  // open the serial port:
  Serial.begin(9600);
  updateLocation(x);

}
void loop() {
  // check for incoming serial data:
  char inChar = 0;
  if (Serial.available() > 0) {
    // read incoming serial data:
   inChar = Serial.read();
    // Type the next ASCII value from what you received:
  }
  if (inChar =='w')
  {
    x = x-1;
    x=checkVerticalBountary(x, inChar);
    updateLocation(x);
  }

  else if (inChar =='s')
  {
    x = x+1;
    x=checkVerticalBountary(x, inChar);
    updateLocation(x);
  }
  else if (inChar =='a')
  {
    x = x-8;
    x=checkHorizontalBountary(x);
    updateLocation(x);
  }
  else if (inChar == 'd')
  {
    x = x+8;
    x=checkHorizontalBountary(x);
    updateLocation(x);
  }
  else if (inChar =='f')
  {
    if(location[x]==1)
    {
      location[x]=2;
    }
    else
    {
      location[x]=0;
    }
    updateLocation(x);
  }
}
void updateLocation (int x)
{
  //memset(location,0,sizeof(location));
  //easiest way to reset all array to zero
  initLocation();
  if (location[x] != 2) {location[x] = 1;}
  for (int j = 0; j < 8; j++){
  for (int i = 0; i < 8; i++) 
  {
    Serial.print(location[j+8*i]);
    Serial.print("  ");
  }
  Serial.println("");
  }
Serial.println("----------------------------------------------");
  
}
int checkHorizontalBountary(int x)
{
  if (x<0)
  {
    x = x+64;
  }
  else if (x>63)
  {
    x = x-64;
  }
  return x;
}

int checkVerticalBountary(int x, char joystick)
{
   if ((x+1)%8==0 && joystick=='w')
  {
    x = x+8;
  }
  else if (x%8 ==0 && joystick=='s')
  {
    x = x-8;
  }
  return x;
}

void initLocation()
{
   for (int j = 0; j < 64; j++)
   {
      if(location[j]!=2)
      {
        location[j]=0;
      }
   }
}
