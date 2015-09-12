#include <ATL_IO.h>
#include <ATL_Process.h>

// Our OutputPinTask class glues the OnTimeout of the TimeoutTask to the Toggle of the DigitalOutputPin
#include "OutputPinTask.h"

using namespace ATL;

/*
 * TimeoutTask uses the Task macros to implement a (software) timer.
 * It requires the use of the Delays<> class that keeps track of wait-times. 
 */

// Delays is a static class - no instance is created.
typedef Delays<Time<Milliseconds>, 4> TaskSchedule;

/*
 * The following outputs are set:
 * Pin 13 (on board led)
 * Pin 12
 * Pin 11
 * Pin 10
 * 
 * Attach LEDs with current limiting resistors (220 ohm) to see the tasks' output.
 */
TimeoutTask<OutputPinTask<13>, TaskSchedule, 1000> task1;
TimeoutTask<OutputPinTask<12>, TaskSchedule, 200> task2;
TimeoutTask<OutputPinTask<11>, TaskSchedule, 500> task3;
TimeoutTask<OutputPinTask<10>, TaskSchedule, 1500> task4;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // update the scheduler - this counts down the wait-times
  TaskSchedule::Update();
  
  task1.Execute();
  task2.Execute();
  task3.Execute();
  task4.Execute();
  
}
