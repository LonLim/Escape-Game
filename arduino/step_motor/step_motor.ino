#include <Stepper.h>
#define STEPS 32

Stepper stepper (STEPS, 35, 33, 31, 29);

int val = 0;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(200);
}

void loop() {
  if (Serial.available()>0)
  {
    val = Serial.parseInt();
    stepper.step(val);
    Serial.println(val); //for debugging
  }

}
