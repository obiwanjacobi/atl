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

#ifndef __FIXEDARRAYREF_H__
#define __FIXEDARRAYREF_H__

#include <stdint.h>
#include "ArrayRef.h"

namespace ATL {


    /** The FixedArrayRef adds methods that change the ArrayRef.
     *  Fixed refers to its size, it's predetermined when it is constructed.
     *  \tparam T the datatype of the items in the array.
     *  \tparam MaxItems is the maximum number of items in the array.
     */
    template<typename T, const uint16_t MaxItems>
    class FixedArrayRef : public ArrayRef < T, MaxItems >
    {
        typedef ArrayRef<T, MaxItems> BaseT;

    public:
        /** ItemT defines the type of array items.
         */
        typedef T ItemT;

        /** Constructs and instance with a reference to an array.
         *  \param array points to the array.
         */
        FixedArrayRef(T* array)
            : BaseT(array)
        { }

        /** Assigns the item to the specified position (index).
         *  Does nothing when the index is invalid.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than MaxItems.
         *  \param item is the new value for the position indicated by index.
         */
        inline void SetAt(int16_t index, T value)
        {
            if (!BaseT::IsValidIndex(index)) return;

            BaseT::getBuffer()[index] = value;
        }

        /** Clears the memory occupied by the array.
         *  All bytes are reset to 0 (zero).
         */
        inline void Clear()
        {
            memset(BaseT::getBuffer(), 0, MaxItems);
        }
    };


} // ATL

#endif //__FIXEDARRAYREF_H__