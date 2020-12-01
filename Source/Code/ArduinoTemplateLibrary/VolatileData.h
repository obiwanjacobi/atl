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

#ifndef __VOLATILEDATA_H__
#define __VOLATILEDATA_H__

namespace ATL {

    // container class for volatile RAM data
    template<typename T>
    class VolatileData
    {
    public:
        VolatileData(T data)
        {
            Data = data;
        }

        inline T operator T() const
        {
            return Data;
        }
        inline operator=(T data)
        {
            Data = data;
        }

        volatile T Data;
    };

} // ATL

#endif //__VOLATILEDATA_H__