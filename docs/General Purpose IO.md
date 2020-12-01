# General Purpose IO

ATL comes with a couple of convenience classes for working with general purpose IO (pins).

## Digital IO

The `DigitalInputPin` and `DigitalOutputPin` classes encapsulate the initialization and direction of a board IO pin. These template classes use a template parameter to specify the pin number, thereby saving another byte in RAM.

This example defines a digital output for controlling the on-board LED on pin 13 and turns it on.

```cpp
  DigitalOutputPin<13> onBoardLED;

  onBoardLED.Write(true);
```

## Analog IO

Similar the `AnalogInputPin` (not implemented yet) and `AnalogOutputPin` classes work with the ADC inputs and the PWM outputs. Note that the AnalogOutputPin derives from the DigitalOutputPin class and can therefor also be used as a digital pin.

## Serial IO

ATL has a `Serial3WireOutput` class that is designed to operate on one or more 74HC595 shift registers. Using only 3 wires an 'endless' number of output pins can be created cascading these chips together. This class takes care of clocking the data into the shift registers and latching it to the output pins. It uses a `BitArray<T>` to store the individual bits for each output pin.

The `Serial3WireOutput` class can be used as a BaseT for a Driver class that implements Driver logic for a specific device (IC) through the shift registers.

Currently no PWM is implemented on these outputs yet.
