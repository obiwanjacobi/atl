#include <ATL IO.h>

using namespace ATL;

DigitalOutputPin<13> led;
bool value;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  led.Write(value);
  value = !value;
  
  delay(200);
}
