#include <ATL_IO.h>

using namespace ATL;

// The StreamOutputStream class adapts an ATL Output Stream to an Arduino Stream (HardwareSerial)
// The TextWriter class writes to the ATL Output Stream
TextWriter<StreamOutputStream<HardwareSerial> > textStream;

// Open the serial terminal on the Arduino IDE before running!
// Set the serial monitor to 'Both NL & CR'

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Attach the Arduino Serial connection to the ATL text stream.
  textStream.AttachOutputStream(&Serial);

  // Note: Set the serial monitor to 'Both NL & CR'
  textStream.WriteLine("Hello World!");
  textStream.WriteLine(42);
  // note that not all digits are displayed. See also TextFormatInfo.
  textStream.WriteLine(3.141592f);
}

void loop() {
  // put your main code here, to run repeatedly:

}
