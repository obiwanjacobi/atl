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

#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <stdint.h>
#include "Default.h"

namespace ATL {

    /** The Iterator class maintains a current index of the iteration position.
     *  It can move this position forward and backwards but does not wrap around the beginning or the end (See WrapAroundIterator).
     *  Either MoveNext, MoveBack or MoveTo methods must be called before there is a valid current item.
     *	\tparam BaseT is expected to implement the Array interface: 
     *	`typedef ItemT` (the item type in the array)
     *	`ctor(const ItemT*)`
     *	`bool IsValidIndex(int16_t) const`
     *	`int16_t IndexOf(ItemT) const`
     *	`ItemT GetAt(int16_t) const`
     *  `uint16_t getCount() const`.
     */
    template<class BaseT>
    class Iterator : public BaseT
    {
    public:
        /** ItemT defines the type of array items.
         */
        typedef typename BaseT::ItemT ItemT;

        /** Constructs the instance.
         */
        Iterator()
            : _index(-1)
        { }

        /** Constructs an initialized instance.
         *  \param array points to the array.
         */
        Iterator(const ItemT* array)
            : BaseT(array), _index(-1)
        { }

        /** Moves to the next item.
         *  \return Returns true when successful.
         */
        inline bool MoveNext()
        {
            if (BaseT::IsValidIndex(_index + 1))
            {
                _index++;
                return true;
            }

            return false;
        }

        /** Moves to the previous item.
         *  \return Returns true when successful.
         */
        inline bool MoveBack()
        {
            if (BaseT::IsValidIndex(_index - 1))
            {
                _index--;
                return true;
            }

            return false;
        }

        /** Moves to the specified item.
         *  \param item is the item to find.
         *  \return Returns true when successful.
         */
        inline bool MoveTo(ItemT item)
        {
            int16_t i = BaseT::IndexOf(item);

            if (i >= 0)
            {
                _index = i;
                return true;
            }

            return false;
        }

        /** Resets the current position to just before the beginning.
         *  Either MoveNext or MoveTo methods must be called before there is a valid current item.
         */
        inline void Reset()
        {
            _index = -1;
        }

        /** Indicates if the current position is valid.
         *  \return Returns true if valid.
         */
        inline bool getIsValidPosition() const
        {
            return BaseT::IsValidIndex(_index);
        }

        /** Retrieves the item at the current position.
         *  \return Returns the item or a Default value if the current position is not valid.
         */
        inline ItemT getCurrent() const
        {
            if (!BaseT::IsValidIndex(_index)) return Default<ItemT>::DefaultOfT;

            return BaseT::GetAt(_index);
        }

    protected:
        /** Resets the current position to just after the end.
         *  Either MoveBack or MoveTo methods must be called before there is a valid current item.
         */
        inline void ResetToEnd()
        {
            _index = BaseT::getCount();
        }

    private:
        int16_t _index;
    };


    /** Implements wrap-around behavior on top of the Iterator class.
     *	\tparam BaseT is expected to implement the Array interface:
     *	`typedef ItemT` (the item type in the array)
     *	`ctor(const ItemT*)`
     *	`bool IsValidIndex(int16_t) const`
     *	`int16_t IndexOf(ItemT) const`
     *	`ItemT GetAt(int16_t) const`
     *  `uint16_t getCount() const`.
     */
    template<typename BaseT>
    class WrapAroundIterator : public Iterator<BaseT>
    {
        typedef Iterator<BaseT> IteratorT;

    public:
        /** Moves to the next item.
         *  Starts at the beginning when the end of the array is reached.
         *  \return Always returns true.
         */
        inline bool MoveNext()
        {
            if (!IteratorT::MoveNext())
            {
                IteratorT::Reset();
                IteratorT::MoveNext();
            }

            return true;
        }

        /** Moves to the previous item.
         *  Starts at the end when the beginning of the array is reached.
         *  \return Always returns true.
         */
        inline bool MoveBack()
        {
            if (!IteratorT::MoveBack())
            {
                IteratorT::ResetToEnd();
                IteratorT::MoveBack();
            }

            return true;
        }
    };


} // ATL


#endif //__ITERATOR_H__