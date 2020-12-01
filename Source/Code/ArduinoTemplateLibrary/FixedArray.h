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

#ifndef __FIXEDARRAY_H__
#define __FIXEDARRAY_H__

#include <stdint.h>
#include <string.h>
#include "Array.h"

namespace ATL {

    /** The FixedArray adds methods that change the Array.
     *  Fixed refers to its size, it's predetermined when it is constructed.
     *  \tparam T the datatype of the items in the array.
     *  \tparam MaxItems is the maximum number of items in the array.
     */
    template<typename T, const uint16_t MaxItems>
    class FixedArray : public Array < T, MaxItems >
    {
        typedef Array<T, MaxItems> BaseT;

    public:
        /** ItemT defines the type of array items.
         */
        typedef T ItemT;

        /** Assigns the item to the specified position (index).
         *  Does nothing when the index is invalid.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than MaxItems.
         *  \param item is the new value for the position indicated by index.
         */
        inline void SetAt(int16_t index, T item)
        {
            if (!BaseT::IsValidIndex(index)) return;

            BaseT::getBuffer()[index] = item;
        }

        /** Retrieves the (writable) item (reference) for the specified position (index).
         *  Does nothing when the index is invalid.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than MaxItems.
         *  \return Returns the item value for the position indicated by index. The return value for an invalid index is undetermined.
         */
        inline T& operator[](int16_t index)
        {
            if (!BaseT::IsValidIndex(index)) return DummyOfT;

            return BaseT::getBuffer()[index];
        }

        /** Clears the memory occupied by the array.
         *  All bytes are reset to 0 (zero).
         */
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