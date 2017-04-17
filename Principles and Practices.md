# Principles and Practices

ATL is build with several goals in mind:

* Low Resource Consumption
* Separation of Concerns
* Extensible and Flexible


## Low Resource Consumption

A Microcontroller has limited resources, program memory (Flash-ROM), Data Memory (RAM) and computing power (processor). Usually there is more program memory relative to the data memory and so ATL will lean to using (generating through templates) more code versus using more RAM.

Also we try not to use any of the General Purpose IO or timers that may be on the MCU.

**NOTE**: that several classes that now only exist as templates (using more ProgMem) will be duplicated to 'normal' classes (using more RAM) to allow the developer the choice which is more important to the project.

The following principles are applied by ATL to reduce using up resources:
* Template classes vs. normal classes
* Avoiding the use of virtual methods and thus saving on the extra bytes the vtables would occupy.
* Use template parameters for static information instead of vars,


## BaseT
This is the name of all template parameters that are used to derive the specific class from. It allows the developer to pick and choose and extend or change any class-level in the class hierarchy. The template class that specifies a BaseT template parameter usually requires several methods to be implemented on that type. These are documented at the top of the class declaration.

Using this 'trick' has several benefits:
* No virtual methods to overload and no formal interfaces. 
* Easy to extend and change the services BaseT has to provide (separation of concerns).

A disadvantage of this mechanism is that it suffers in polymorphism. It is harder (or impossible) to treat the same template class with different template arguments as one common type (or interface). The developer must weigh the benefits against this disadvantage when choosing what approach to use.

The chain of template classes stacked by the BaseT template parameter can get quite large. Recommended is to use {{typedef}}'s to have aliases for some common constructs in your program.

Here is an example for declaring two 'types' of the motor controller template classes for a differential driven car.

{{
  typedef TB6612FNG_Controller<TB6612FNG_Driver<8, 9, 10> > LeftWheelController;
  typedef TB6612FNG_Controller<TB6612FNG_Driver<7, 6, 5> > RightWheelController;
}}

The BaseT template parameter of the Controller class is filled in with a Driver template class, which in turn takes the pin numbers used to drive the motor controller IC. The LeftWheelController and RightWheelController types can now be used in the program without the 'noise' of all the template parameters.



_See Also_
[http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern](http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)



