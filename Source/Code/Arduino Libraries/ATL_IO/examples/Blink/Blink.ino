#include <ATL_IO.h>

using namespace ATL;

DigitalOutputPin<13> led;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  led.Toggle();
  
  delay(200);
}

