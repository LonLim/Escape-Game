#define laser_Sensor A2 // pin 2 for  sensor
#define laser 2

void setup() {
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
}

void loop() {
  int detected = analogRead(laser_Sensor);// read Laser sensor
  Serial.println(detected);
 }
