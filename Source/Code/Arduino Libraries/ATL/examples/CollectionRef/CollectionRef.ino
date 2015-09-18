#include <ATL.h>

using namespace ATL;

/*
 * A CollectionRef references an Array or ArrayRef and 
 * implements adding items - up until the max boundary of the underlying array.
 * 
 * CollectionRef allows you to statically allocate memory (through Array)
 * but still use it in a dynamic way (Add). Using Array(Ref) an alternative for 
 * specifying a MAX_NUMBER_OF_ITEMS macro for each collection in your program.
 */

// use typedef for easy reuse.
typedef FixedArray<int, 2> IntArray;

IntArray myArray;
CollectionRef<IntArray> myCollection(myArray);

void setup() {
  // put your setup code here, to run once:

  // dynamically add values
  myCollection.Add(42);
  myCollection.Add(42);
  myCollection.Add(42);

  // protects agains overrun
  myCollection.Add(42);

  // iterate through the items in the collection
  for(unsigned char i = 0; i < myCollection.getCount(); i++)
  {
    int value = myCollection[i];
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
