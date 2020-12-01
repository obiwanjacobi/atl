/*
Arduino Template Library https://github.com/obiwanjacobi/atl
Written by Marc Jacobi
Copyright 2012-2015 All Rights Reserved

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __ENUMSCOPE_H__
#define __ENUMSCOPE_H__

/** MACRO: Starts an enum with a scope (See also EndEnum).
 *	Values for the enum has to be scoped with the enum name. e.g. `Color::Red`.
 *  BeginEnum(Color)
 *  {
 *      Red,
 *      Green,
 *      Blue
 *  }
 *  EndEnum(Color)
 *	\param name is the name of the enum.
 */

#define BeginEnum(name) \
struct name { \
public: \
    enum type \
        
/** MACRO: Ends an enum with a scope (See also BeginEnum).
 *	\param name is the name of the enum.
 */
#define EndEnum(name) ; \
    name(type val) : value(val) {} \
    operator type() const { return value; } \
    type value; \
private: template<typename T> operator T () const; \
};\

/** MACRO: Ends an enum with a scope (See also BeginEnum).
*	Allows specifying a default value.
*	\param name is the name of the enum.
*	\param default is the default value for the enum.
*/
#define EndEnum2(name, default) ; \
    name(type val = default) : value(val) {} \
    operator type() const { return value; } \
    type value; \
private: template<typename T> operator T () const; \
};\


#endif /* __ENUMSCOPE_H__ */