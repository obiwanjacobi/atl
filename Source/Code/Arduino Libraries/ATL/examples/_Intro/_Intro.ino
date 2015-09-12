#include <ATL.h>

/*
 * Welcome to the Arduino Template Library (ATL).
 * http://atl.codeplex.com
 *
 * ATL uses some techniques you may not be familiar with.
 * This intro sketch (that does nothing) explains these techniques.
 * 
 * 
 * =================================
 * NAMESPACES
 * =================================
 * All ATL code is declared inside the ATL namespace.
 * Namespaces prevent name clashes with other (library) code.
 * 
 * There are two ways to access classes from the ATL namespace:
 * 1) Use the fully qualified name
 *     ATL::Array<int, 5> myArray;
 * 
 * 2) 'using namespace ATL;'
 *     Array<int, 5> myArray;
 * 
 * The first way is excellent for when you run into duplicate type names
 * between ATL classes and other (library) classes.
 * The second way is very convinient and make the code a little easier to read.
 * 
 * If you get compiler errors that a (ATL) type could not be found
 * you have probably not specified the namespace (one of the two 
 * methods mentioned above).
 * 
 * 
 * =================================
 * TEMPLATE CLASSES
 * =================================
 * A template class is a C++ class where some aspects have not been specified 
 * and are left as a type parameter.
 * This provides another level of flexibility when using the classes but may generate
 * extra program code (flash memory). With these techniques ATL attempts to minimize
 * the use of RAM memory.
 * 
 * Several template classes in ATL have a type parameter called BaseT. This indicates that
 * that type is used to derive from. The puts the template class on the 'outside' of the class
 * hierarchy. This can be used to reduce the need for virtual methods (no or smaller v-tables)
 * but also allows a very high level of flexibility and extensibility.
 * 
 * The down side is that the type declarations may become a bit large. By using typedef's
 * your code will stay clean and very readable.
 * 
 * 
 * =================================
 * USING TYPEDEF
 * =================================
 * When a template class hierarchy is defined with lots of classes that all have a BaseT
 * template parameter a long string of nested template declaration is the result. It would
 * be cumbersome to repeat this declaration each time you refer to the type.
 * 
 * By using the 'typedef' keyword you declare the (complex) type once and give it an alias to
 * use in the rest of your code. Here's an example for the LCD display:
 * 
 * typedef  TextWriter<
 *            HD44780_View<
 *              HD44780_Controller<
 *                HD44780_Driver<
 *                  DigitalOutputPin<2>,  // register select
 *                  DigitalOutputPin<3>,  // enable
 *                  DigitalOutputPin<4>,  // bit 0 / bit 4
 *                  DigitalOutputPin<5>,  // bit 1 / bit 5
 *                  DigitalOutputPin<6>,  // bit 2 / bit 6
 *                  DigitalOutputPin<7>   // bit 3 / bit 7
 *                >
 *              >, 2, 16        // 2 lines, 16 characters
 *            >
 *          > LCD;
 *
 * As you can see the declaration is quite complex but thanks to the typedef we can now
 * refer to it simply as 'LCD'.
 * 
 * 
 * Have fun!
 * 
 */

 

