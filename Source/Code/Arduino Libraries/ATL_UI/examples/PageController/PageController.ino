#include <ATL_HD44780.h>
#include <ATL_IO.h>
#include <ATL_UI.h>

using namespace ATL;

typedef HD44780_DisplayWriter<
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
LabelControl label3("Line 3");
LabelControl label4("Line 4");

// 2 lines (with only one control each) on the display
Line<1> line1(&label1);
Line<1> line2(&label2);
Line<1> line3(&label3);
Line<1> line4(&label4);

// the page that is shown on the display
Page<2> page1(&line1, &line2);
Page<2> page2(&line3, &line4);

PageController<2, 2> pageCtrlr;

void setup() {
  // put your setup code here, to run once:

  // add pages to controller
  pageCtrlr.Add(&page1);
  pageCtrlr.Add(&page2);

  // init and enable display
  lcd.Initialize(true);
  lcd.setEnableDisplay();

  pageCtrlr.TrySetFirstPage();

  // display the first page
  pageCtrlr.Display(&lcd);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);
  
  if (!pageCtrlr.TrySetNextPage())
  {
    pageCtrlr.TrySetFirstPage();
  }

  // display the page
  pageCtrlr.Display(&lcd);
}

