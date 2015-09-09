#ifndef __COUNTERTASK_H__
#define __COUNTERTASK_H__

// Our task that counts...
class CounterTask
{
public:
  // constructs an object with the max-count.
  CounterTask(long maxCount) : _counter(0), _maxCount(maxCount)
  {}
    
  /*
   * Between the Task_Begin and Task_End macros is your method that defines the process of your task.
   * bool GlobalTask() - return value indicates if we yielded (true) or naturally exited the function (false).
   */
  Task_Begin(Execute)
  {
    // no - this will not hang the program ...
    while(true)
    {
      // ... because we yield from this method (that is the magic!)
      Task_YieldUntil(IncrementCount());
      /* Execution will exit (yield) and enter (next call to Execute) exactly here (Task_YieldUntil).
       * So make sure you perform the action required by the task (for this part) in one method.
       */

       // execution falls through when IncrementCount returned true.
      _counter = 0;
      Serial.print("Counted to ");
      Serial.println(_maxCount);
    }
  }
  Task_End

private:
  // returns true if the count has been reached.
  bool IncrementCount()
  {
    _counter++;
    return _counter > _maxCount;
  }

  // vars used by our task
  long _counter;
  long _maxCount;

  // This var is used by the macro's to maintain the state of the process 
  // and must always be present for each Task method (only one task method per class).
  int _task;
};

#endif //__COUNTERTASK_H__
