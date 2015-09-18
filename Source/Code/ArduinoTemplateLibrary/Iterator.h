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

#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <stdint.h>
#include "Default.h"

namespace ATL {

/*
 *	BaseT is an Array type and implements
 *		typedef ItemT (the item type in the array)
 *		ctor(const ItemT*)
 *		bool IsValidIndex(int16_t) const
 *		int16_t IndexOf(ItemT) const
 *		ItemT GetAt(int16_t) const
 *      uint16_t getCount() const
 */
template<class BaseT>
class Iterator : public BaseT
{
public:
	Iterator()
		: _index(-1)
	{ }

	Iterator(const typename BaseT::ItemT* array)
		: BaseT(array), _index(-1)
	{ }

	inline bool MoveNext()
	{
		if (BaseT::IsValidIndex(_index + 1))
		{
			_index++;
			return true;
		}

		return false;
	}

	inline bool MoveBack()
	{
		if (BaseT::IsValidIndex(_index - 1))
		{
			_index--;
			return true;
		}

		return false;
	}

	inline bool MoveTo(typename BaseT::ItemT item)
	{
		int16_t i = BaseT::IndexOf(item);

		if (i >= 0)
		{
			_index = i;
			return true;
		}

		return false;
	}

	inline void Reset()
	{
		_index = -1;
	}

    inline bool getIsValidPosition() const
    {
        return BaseT::IsValidIndex(_index);
    }

	inline typename BaseT::ItemT getCurrent() const
	{
		if (!BaseT::IsValidIndex(_index)) return Default<typename BaseT::ItemT>::DefaultOfT;

		return BaseT::GetAt(_index);
	}

protected:
    inline void ResetToEnd()
    {
        _index = BaseT::getCount();
    }

private:
	int16_t _index;
};



template<typename BaseT>
class WrapAroundIterator : public Iterator<BaseT>
{
    typedef Iterator<BaseT> IteratorT;

public:
    inline bool MoveNext()
    {
        if (!IteratorT::MoveNext())
        {
            IteratorT::Reset();
            IteratorT::MoveNext();
        }

        return true;
    }

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