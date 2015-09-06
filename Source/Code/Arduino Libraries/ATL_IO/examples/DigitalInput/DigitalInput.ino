#include <ATL_IO.h>

using namespace ATL;

DigitalOutputPin<13> led;

// DigitalInput maintains state of the last value read.
DigitalInput<DigitalInputPin<4> > input4;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // Read returns true when a new/other value was read
  if (input4.Read())
  {
    led.Write(input4.getValue());
  }

  delay(200);
}
