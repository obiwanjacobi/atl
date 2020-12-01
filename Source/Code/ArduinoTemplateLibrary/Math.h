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

#ifndef __MATH_H__
#define __MATH_H__

namespace ATL {

    /** Math provides math functions.
     *  The Math class is a static class and cannot be instantiated.
     */
    class Math
    {
    public:
        /** Returns the absolute value.
         *  \tparam T is the data type of the value.
         *  \param value is the value to return the non-negative representation for.
         *  \return Returns the non-negative value.
         */
        template<typename T>
        inline static T Abs(T value)
        {
            return value >= 0 ? value : -value;
        }

    private:
        Math() { }
    };

} // ATL

#endif //__MATH_H__