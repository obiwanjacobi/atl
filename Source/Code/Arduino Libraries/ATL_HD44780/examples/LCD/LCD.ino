#include <ATL_HD44780.h>
#include <ATL_IO.h>

using namespace ATL;

typedef  TextWriter<
            HD44780_View<
              HD44780_Controller<
                HD44780_Driver<
                  DigitalOutputPin<2>,  // register select
                  DigitalOutputPin<3>,  // enable
                  DigitalOutputPin<4>,  // bit 0 / bit 4
                  DigitalOutputPin<5>,  // bit 1 / bit 5
                  DigitalOutputPin<6>,  // bit 2 / bit 6
                  DigitalOutputPin<7>   // bit 3 / bit 7
                >
              >, 2, 16        // 2 lines, 16 characters
            >
          > LCD;

LCD lcd;

void setup() {
  // put your setup code here, to run once:

  // fully initialize the lcd.
  lcd.Initialize(true);
  
  // turn it on
  lcd.setEnableDisplay();

  // use TextWriter to output a string
  lcd.WriteLine("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
