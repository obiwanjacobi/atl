#include <ATL.h>

using namespace ATL;

/*
 * Besides Bit and BitFags, ATL has a BitArray to access bits as an array.
 * Can be used to store data more effectively by combining multiple 
 * logical vars in specific bit-index ranges.
 */

// The data type specified dictates how many bits are available.
BitArray<unsigned short> arrayOf16Bits;

void setup() {
  // put your setup code here, to run once:

  // single bit access:
  // set bit-index 2 (true);
  arrayOf16Bits.Set(2);
  // test bit-index 2
  if (arrayOf16Bits.IsTrue(2))
  { /* some code here */ }

  // reset all bits (false)
  arrayOf16Bits.ResetAll();

  // bit range access:
  // set least-significant nibble
  arrayOf16Bits.Set(0, 0xF, 4);
  // bit-ranges are return as the template type paramater
  unsigned short nibble = arrayOf16Bits.Get(0, 4);

  // special operations:
  // reverses the position of all bits
  arrayOf16Bits.Reverse();
  // shift all bits down one nibble (lose the least significant nibble).
  arrayOf16Bits.ShiftDown(4);
}

void loop() {
  // put your main code here, to run repeatedly:

}
