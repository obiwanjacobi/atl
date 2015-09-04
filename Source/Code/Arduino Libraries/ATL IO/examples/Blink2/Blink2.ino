#include <ATL IO.h>

using namespace ATL;
using namespace ATL::IO;

DigitalOutput<DigitalOutputPin<13> > led;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  led.Write(!led.getValue());
  
  delay(200);
}
