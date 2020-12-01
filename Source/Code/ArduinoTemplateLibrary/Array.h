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

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdint.h>
#include "Default.h"

namespace ATL {

    /** Represents a bounds-checked (read-only) array.
     *  \tparam T is the type of the array items.
     *  \tparam MaxItems is the maximum number of items in the array.
     */
    template<typename T, const uint16_t MaxItems>
    class Array
    {
    public:
        /** ItemT defines the type of array items.
         */
        typedef T ItemT;

        /** Gets the maximum number of items the array can store.
         *  \return Returns the MaxItems template parameter.
         */
        inline uint16_t getCapacity() const
        {
            return MaxItems;
        }

        /** Gets the current number of items in the array.
         *  \return Returns the MaxItems template parameter.
         */
        inline uint16_t getCount() const
        {
            return MaxItems;
        }

        /** Gets the item at the zero-based index position.
         *  If the specified index is invalid a default value for T is returned. See also Default<T>::DefaultOfT.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than MaxItems. 
         *  \return Returns the item or a default value.
         */
        inline T GetAt(int16_t index) const
        {
            if (!IsValidIndex(index)) return Default<T>::DefaultOfT;

            return _arr[index];
        }

        /** Indicates if the specified index is valid for the array.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than MaxItems.
         *  \return Returns true when the index is valid, otherwise false.
         */
        inline bool IsValidIndex(int16_t index) const
        {
            return index >= 0 && index < (int16_t)MaxItems;
        }

        /** Finds the index of the first matching item in the array.
         *  Be careful with arrays that contain duplicate items.
         *  \param item is the item to search for.
         *  \return Returns the index of the position of the item in the array, or -1 if not found.
         */
        inline int16_t IndexOf(T item) const
        {
            for (int16_t i = 0; i < (int16_t)MaxItems; i++)
            {
                if (_arr[i] == item)
                    return i;
            }

            return -1;
        }

        /** Gets the item at the zero-based index position.
         *  If the specified index is invalid a default value for T is returned. See also Default<T>::DefaultOfT.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than MaxItems.
         *  \return Returns the item or a default value.
         */
        inline T operator[](int16_t index) const
        {
            return GetAt(index);
        }

        /** Provides access to the internal buffer that stores the items in the array.
         *  Not recommended to use this because no bounds checking is performed.
         *  \return Returns the pointer to the buffer.
         */
        inline T* getBuffer()
        {
            return _arr;
        }

    private:
        T _arr[MaxItems];
    };


} // ATL

#endif //__ARRAY_H__