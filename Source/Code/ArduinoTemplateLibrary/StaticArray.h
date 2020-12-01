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

#ifndef __STATICARRAY_H__
#define __STATICARRAY_H__

#include <stdint.h>
#include "ProgMemAccessor.h"
#include "ArrayRef.h"

namespace ATL {

    /** The StaticArray class implements the Array interface for arrays that reside in PROGMEM.
     *  \tparam T is the datatype of the items in the array.
     *  \tparam MaxItems is the maximum number of items.
     */
    template<typename T, const uint16_t MaxItems>
    class StaticArray
    {
    public:
        /** The datatype of the items in the array.
         */
        typedef T ItemT;

        /** Constructs an initialized instance.
         *  Declare a PROGMEM array and pass in the variable.
         *  \param array points to the PROGMEM array.
         */
        StaticArray(const T* array)
            : _arr(array)
        { }

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
         *  The value for the item is read using the ProgMemAccessor.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than MaxItems. 
         *  \return Returns the item or a default value.
         */
        inline T GetAt(int16_t index) const
        {
            if (!IsValidIndex(index)) return Default<T>::DefaultOfT;

            return Implementation::ProgMemAccessor<T>::Read(&_arr[index]);
        }

        /** Indicates if the specified index is valid for the array.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than MaxItems.
         *  \return Returns true when the index is valid, otherwise false.
         */
        inline bool IsValidIndex(int16_t index) const
        {
            return index >= 0 && index < MaxItems;
        }

        /** Finds the index of the first matching item in the array.
         *  Be careful with arrays that contain duplicate items.
         *  \param item is the item to search for.
         *  \return Returns the index of the position of the item in the array, or -1 if not found.
         */
        inline int8_t IndexOf(T item) const
        {
            for (uint8_t i = 0; i < MaxItems; i++)
            {
                if (GetAt(i) == item)
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
        inline const T* getBuffer() const
        {
            return _arr;
        }

    protected:
        /** For derived classes.
         *  Call `setBuffer()`.
         */
        StaticArray()
            : _arr(NULL)
        { }

        /** Assigns the array to the internal buffer.
         *  \param array is the pointer to the PROGMEM array.
         */
        inline void setBuffer(const T* array)
        {
            _arr = array;
        }

    private:
        const T* _arr;
    };


} // ATL

#endif //__STATICARRAY_H__