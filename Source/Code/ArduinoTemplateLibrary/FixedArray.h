/*
Arduino Template Library http://atl.codeplex.com
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

#ifndef __FIXEDARRAY_H__
#define __FIXEDARRAY_H__

#include <stdint.h>
#include <string.h>
#include "Array.h"

namespace ATL {

/*
*	Bounds-checked array.
*
*/
template<typename T, const uint16_t MaxItems>
class FixedArray : public Array<T, MaxItems>
{
    typedef Array<T, MaxItems> BaseT;

public:
    typedef T ItemT;

    inline void SetAt(int16_t index, T value)
    {
        if (!BaseT::IsValidIndex(index)) return;

        BaseT::getBuffer()[index] = value;
    }

    // return value for invalid index is undetermined.
    inline T& operator[](int16_t index)
    {
        if (!BaseT::IsValidIndex(index)) return DummyOfT;

        return BaseT::getBuffer()[index];
    }

    inline void Clear()
    {
        memset(BaseT::getBuffer(), 0, MaxItems);
    }

protected:
    static T DummyOfT;

};

template<typename T, const uint16_t MaxItems>
T FixedArray<T, MaxItems>::DummyOfT;


} // ATL

#endif //__FIXEDARRAY_H__