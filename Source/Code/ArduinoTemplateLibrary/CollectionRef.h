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

#ifndef __COLLECTIONREF_H__
#define __COLLECTIONREF_H__

#include <stdint.h>
#include "Default.h"

namespace ATL {


    /** The CollectionRef class implements dynamic behavior of adding items on top of a reference to a FixedArray.
    *  \tparam ArrayT is the array type that is used to store the actual items.
    *  ArrayT implements `T GetAt(int16_t index)`, `void SetAt(int16_t index, T item)` and `uint16_t getCapacity()`.
    */
    template<typename ArrayT>
    class CollectionRef
    {
    public:
        /** The datatype of the items in the collection. */
        typedef typename ArrayT::ItemT ItemT;

        /** Constructs an initialized instance.
         *  \param array refers to the array that is used for storage.
         */
        CollectionRef(ArrayT& array)
            : _array(array), _count(0)
        { }

        /** Gets the maximum number of items the collection can store.
         *  \return Returns the Capacity of the underlying array.
         */
        inline uint16_t getCapacity() const
        {
            return _array.getCapacity();
        }

        /** Gets the current number of items in the collection.
         *  \return Returns the count.
         */
        inline uint16_t getCount() const
        {
            return _count;
        }

        /** Indicates if the specified index is valid for the array.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than the count.
         *  \return Returns true when the index is valid, otherwise false.
         */
        inline bool IsValidIndex(int16_t index) const
        {
            return index >= 0 && index < _count;
        }

        /** Gets the item at the zero-based index position.
         *  If the specified index is invalid a default value for T is returned. See also Default<T>::DefaultOfT.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than the count.
         *  \return Returns the item or a default value.
         */
        inline typename ArrayT::ItemT GetAt(int16_t index) const
        {
            if (!IsValidIndex(index)) return Default<typename ArrayT::ItemT>::DefaultOfT;

            return _array.GetAt(index);
        }

        /** Gets the item at the zero-based index position.
         *  If the specified index is invalid a default value for T is returned. See also Default<T>::DefaultOfT.
         *  \param index is a zero-based index that has to be greater or equal to 0 (zero) and smaller than the count.
         *  \return Returns the item or a default value.
         */
        inline typename ArrayT::ItemT operator[](int16_t index) const
        {
            return GetAt(index);
        }

        /** Finds the index of the first matching item in the collection.
         *  Be careful with collections that contain duplicate items.
         *  \param item is the item to search for.
         *  \return Returns the index of the position of the item in the collection, or -1 if not found.
         */
        inline char IndexOf(typename ArrayT::ItemT& item) const
        {
            for (int i = 0; i < _count; i++)
            {
                if (_array.GetAt(i) == item)
                    return i;
            }

            return -1;
        }

        /** Adds a new item at the end of the collection.
         *  Does nothing when the collection is full.
         *  \param item is the item to add.
         */
        inline void Add(typename ArrayT::ItemT item)
        {
            if (_count < _array.getCapacity())
            {
                _array.SetAt(_count, item);
                _count++;
            }
        }

        /** Sets a new item at the specified index.
         *  Does nothing when the index is not valid.
         *  \param index is the position in the collection that gets overwritten with the new item.
         *  \param item is the new value to store at the index position.
         */
        inline void SetAt(int16_t index, typename ArrayT::ItemT value)
        {
            if (!IsValidIndex(index)) return;

            _array.SetAt(index, value);
        }

        /** Clears the content of the collection.
         *  It simply resets the count and does not call ArrayT::Clear()!
         */
        inline void Clear()
        {
            _count = 0;
        }

    private:
        ArrayT& _array;
        uint16_t _count;
    };


} // ATL

#endif //__COLLECTIONREF_H__