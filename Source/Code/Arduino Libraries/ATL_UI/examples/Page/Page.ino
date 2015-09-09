#include <ATL_HD44780.h>
#include <ATL_IO.h>
#include <ATL_UI.h>
#include "LcdDisplayWriter.h"

using namespace ATL;

typedef LcdDisplayWriter<
          TextWriter<
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
          > 
        > LCD;

LCD lcd;

// some simple UI controls
LabelControl label1("Line 1");
LabelControl label2("Line 2");

// 2 lines (with only one control each) on the display
Line<1> line1(&label1);
Line<1> line2(&label2);

// the page that is shown on the display
Page<2> page(&line1, &line2);

void setup() {
  // put your setup code here, to run once:

  // init and enable display
  lcd.Initialize(true);
  lcd.setEnableDisplay();

  // display the page
  page.Display(&lcd);
}

void loop() {
  // put your main code here, to run repeatedly:

}
