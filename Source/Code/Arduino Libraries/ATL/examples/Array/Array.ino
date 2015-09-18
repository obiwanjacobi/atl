#include <ATL.h>

using namespace ATL;

// declare an array of 4 int's
FixedArray<int, 4> intArray;
// declare an array of 4 float's
FixedArray<float, 4> floatArray;
// declare an array of 4 ptr's (to int's)
FixedArray<int*, 4> ptrArray;

void setup() {
  // put your setup code here, to run once:

  // setting a value on a valid index
  intArray[0] = 42;
  
  // other way of setting a value on a valid index
  // []-operator also used to retrieve a value
  intArray.SetAt(2, intArray[0]);

  // setting or getting a value on an invalid index will not crash or overrun
  intArray[10] = intArray[10];
}

void loop() {
  // put your main code here, to run repeatedly:

}
