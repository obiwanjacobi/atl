#include <ATL_IO.h>
#include "MyTextFormatInfo.h"

using namespace ATL;

// Specify our custom format info class
TextWriter<StreamOutputStream<HardwareSerial>, MyTextFormatInfo> textStream;

// Open the serial terminal on the Arduino IDE before running!
// Set the serial monitor to 'Newline'

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Attach the Arduino Serial connection to the ATL text stream.
  textStream.AttachOutputStream(&Serial);

  // Note: Set the serial monitor to 'Newline'
  textStream.WriteLine("Hello World!");
  // Displayed as HEX
  textStream.WriteLine(42);
  // Note that not all digits are displayed. 4 digits defined in MyTextFormatInfo.
  // And the decimal separator has been changed to a comma.
  textStream.WriteLine(3.141592f);
}

void loop() {
  // put your main code here, to run repeatedly:

}
