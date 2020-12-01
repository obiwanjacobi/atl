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

#ifndef __DATA_H__
#define __DATA_H__

namespace ATL {


    // container class for RAM data
    template<typename T>
    class Data
    {
    public:
        Data(T data)
        {
            Value = data;
        }

        inline operator T() const
        {
            return Value;
        }

        inline void operator=(T& data)
        {
            Value = data;
        }

        inline void operator|=(T& data)
        {
            Value |= data;
        }

        inline void operator&=(T& data)
        {
            Value &= data;
        }

        T Value;
    };


} // ATL

#endif //__DATA_H__