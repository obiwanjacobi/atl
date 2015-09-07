#include <ATL.h>

using namespace ATL;

/*
 * ATL has two way's to manipulate bits. See also BitArray.
 * 
 * Bit fixes the bit-no as a template parameter. Ideal when the bit number is hard-coded.
 * BitFlag allows you to specify it al in the method call. Use when bit number is dynamic.
 * 
 */

// Bit<3> bit3;      <= error! Bit is a static class!
// BitFlag bitFlag;  <= error! BitFlag is static class too!

void setup() {
  // put your setup code here, to run once:

  int intValue = 0;
  unsigned char ucValue = 0;

  // Use static method to set bit-3 (true) on value
  Bit<3>::Set(intValue);
  Bit<3>::Set(ucValue);

  // Use static method to reset bit-r (false) on value
  BitFlag::Set(intValue, 3, false);
  BitFlag::Set(ucValue, 3, false);
}

void loop() {
  // put your main code here, to run repeatedly:

}
