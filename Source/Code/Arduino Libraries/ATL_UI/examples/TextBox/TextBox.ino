#include <ATL.h>
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

const char chars[] PROGMEM = " +-()0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

// sizeof(chars) -1 because sizeof includes the terminating /0.
typedef Iterator<StaticArray<char, sizeof(chars) - 1> > CharacterIteratorT;

FixedString<6> textBuffer;
CharacterIteratorT charIterator(chars);
// The TextControl will edit the string in textBuffer using the characters provided by the charIterator.
TextControl<FixedString<6>, CharacterIteratorT> text1(&textBuffer, &charIterator, 8); // 8 is column position

// 2 lines (with only one control each) on the display
Line<2> line1(&label1, &text1);
Line<2> line2(&label2);

// the page that is shown on the display
Page<2> page(&line1, &line2);

void setup() {
  // put your setup code here, to run once:
  
  // init and enable display
  lcd.Initialize(true);
  lcd.setEnableDisplay();

  // set the inital text (referenced by the TextControl).
  textBuffer = "Hello ";

  // display the page
  page.Display(&lcd);

  // prelude to navigation
  page.OnNavigationCommand(Down);
}


const NavigationCommands pgmNavCmds[] PROGMEM = { Up, Right, Enter, Up, Up, Up, Right, Up, Up, Up, Up, Exit, Down };
StaticArray<NavigationCommands, 13> navCmds(pgmNavCmds);

void loop() {
  // put your main code here, to run repeatedly:
  
  for(uint16_t i = 0; i < navCmds.getCapacity(); i++)
  {
    page.OnNavigationCommand(navCmds[i]);
    page.Display(&lcd);
    
    delay(600);
  }

  delay(1000);
}

