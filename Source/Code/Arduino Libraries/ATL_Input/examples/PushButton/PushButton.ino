#include <ATL_Input.h>
#include <ATL_IO.h>

using namespace ATL;

// Delays is a static class - no instance is created.
typedef Delays<Time<Milliseconds>, 1> TaskSchedule;

#define DEBOUNCE_TIMEOUT 10  //ms
#define HOLD_TIMEOUT 400  //ms

/*
 * The push button is implemented as a task. This way measuring debounce and hold timeouts are not blocking to other code.
 * They might be a little less precise but for buttons, that is usually not a problem.
 * 
 * Connect the (normally open) switch between A0 and ground. The last template parameter 'true' reverses the logic (0 => on).
 */
PushButton<IdentifiableObject<DigitalInputPin<A0> >, TaskSchedule, DEBOUNCE_TIMEOUT, HOLD_TIMEOUT, true> button;

DigitalOutputPin<13> led;

void setup() {
  // put your setup code here, to run once:

  // because PushButton derives from DigitalInputPin we can treat it as such.
  button.EnableInternalPullup();
}

void loop() {
  // put your main code here, to run repeatedly:

  // update the scheduler - this counts down the wait-times used by the PushButton's timeouts
  TaskSchedule::Update();

  // this is the task method and must be called repeatedly
  button.ScanButton();

  switch(button.getState())
  {
  case stateOpen:
    led.Write(false);
    break;
  case stateClosed:
    led.Write(true);
    break;
  case stateHold:
    led.Toggle();   // this will dim the led due to the loop speed (pwm).
    break;
  default:
    break;
  }
}

