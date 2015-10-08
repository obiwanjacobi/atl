#include <Wire.h>
#include <ATL_HD44780.h>
#include <ATL_IO.h>

using namespace ATL;

/* Connections:
 * I2C-LCD board    Arduino
 * GND              GND
 * VCC              5V (!Check if your board is 5V -or- 3.3V!)
 * SDA              A4
 * SCL              A5
 */

/* I2C Addresses!
 * I2C works with addresses. If the address is incorrect (here we use 0x27) it will not work.
 * Use a sketch called I2cScanner to find the address of the I2c-LCD Board (you can find it online).
 */
#define SLAVE_ADDRESS 0x27

typedef  TextWriter<
            HD44780_View<
              HD44780_Controller<
                HD44780_DriverI2C<
                  SerialI2COutput<SLAVE_ADDRESS>
                >
              >, 2, 16        // 2 lines, 16 characters
            >
          > LCD;

LCD lcd;

void setup() {
  // put your setup code here, to run once:
  
  // ATL reuses the Arduino Wire library.
  // Init I2C as master
  Wire.begin();

  // fully initialize the lcd.
  lcd.Initialize(true);
  
  // this driver supports turning the backlight on and off.
  lcd.setEnableBacklight();
  
  // turn it on
  lcd.setEnableDisplay();

  // use TextWriter to output a string
  lcd.WriteLine("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
