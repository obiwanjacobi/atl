# Hardware

ATL implements classes that represent and/or work with hardware ICs. As a general pattern this interfacing is always divided into two (or more if appropriate) classes.

* Driver - implements how the hardware is interfaced to the Arduino.
* Controller - implements the protocol to talk to the interfaced hardware.

The benefit of this separation is that the Controller logic which is always the same for a specific device or IC does not have to be touched when changing the way the device interfaces with the Arduino. Say a Driver initially is implemented using the Arduino's on-board pin's that are connected to the device in your schematic. When you wish to change that interfacing to say- a {{Serial3WireOutput}}, only the driver class needs to be replaced. So by separating the Driver from the Controller a minimal effort is required to adapt the code to your situation and a maximum amount of reuse is possible (the Controller).


The following hardware devices are currently supported:
* 74HC595 shift registers. See [General Purpose IO](General-Purpose-IO) - Serial IO.
* [HD44780](HD44780) LCD display.
* [TB6612FNG](TB6612FNG) Motor Controller.
* [URM37 V3.2](URM37-V3.2) Sonic Sensor.



