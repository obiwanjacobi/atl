#include <ATL_Process.h>
/*
 * ATL comes with a cooperative multi tasking 'class'. This allows you to run multiple 'tasks' simultaniously
 * without adding too much complexity. 
 * As we will see it is not really a class, but a bunch of macro's but they are meant to be used in a class. 
 * That class is what you write and represents your task.
 * 
 * The Arduino IDE gets confused when you implement a task directly in the sketch, which causes compile errors.
 * See CounterTask.cpp for the task implementation.
 */

#include "CounterTask.h"
// we run two counter tasks at the same time.
CounterTask task1(99999);
CounterTask task2(7777);

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("Counter Task demo:");
}

void loop() {
  // put your main code here, to run repeatedly:

  // call our task processes repeatedly.
  task1.Execute();
  task2.Execute();
}
