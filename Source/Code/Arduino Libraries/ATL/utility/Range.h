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

#ifndef __RANGE_H__
#define __RANGE_H__

namespace ATL {

/*
    The Range class contains 2 values for which in- and out of range check can be performed.
 */
template<typename T>
class Range
{
public:
	Range()
	{
	}

	Range(T begin, T end)
	{
		Begin = begin;
		End = end;
	}

	T Begin;
	T End;

	bool IsInRange(const T value) const
	{
		if (Begin > End)
		{
			return (End <= value && value <= Begin);
		}

		return (Begin <= value && value <= End);
	}

	void Normalize()
	{
		if (Begin > End)
		{
			T temp = End;
			End = Begin;
			Begin = temp;
		}
	}

	inline bool IsNormalized() const
	{
		return (End >= Begin);
	}

	void ClipValue(T& inoutValue) const
	{
		if (inoutValue > End)
		{
			inoutValue = End;
		}
		if (inoutValue < Begin)
		{
			inoutValue = Begin;
		}
	}
};

} //ATL

#endif //__RANGE_H__