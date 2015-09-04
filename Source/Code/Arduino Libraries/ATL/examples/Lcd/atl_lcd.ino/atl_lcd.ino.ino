#include <ATL.h>

// use the ATL namespace(s)
using namespace ATL;
using namespace ATL::Hardware::Display;

// LCD-Driver configures all the board pins.
// LCD-Controller implements the protocol to talk to the LCD
// LCD-View keeps track of cursor position and implements a output stream
// TextWriter implements text formatting functions for easy writing to the LCD
typedef TextWriter< 
          HD44780_View< 
            HD44780_Controller< 
              HD44780_Driver<
                DigitalOutputPin<2>,
                DigitalOutputPin<3>,
                DigitalOutputPin<4>,
                DigitalOutputPin<5>,
                DigitalOutputPin<6>,
                DigitalOutputPin<7>
              >
            >
            2, 16
          >
        > LCD;

// declare an instance of the LCD type.
LCD lcd;

void setup() {
  // do a full initialize of the LCD
  lcd.Initialize(true);

}

unsigned long counter;

void loop() {
  // display the counter value
  lcd.Write(counter);  
  counter++;
  
  delay(200);
}
