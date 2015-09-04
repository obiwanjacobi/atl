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

#ifndef __BIT_H__
#define __BIT_H__

namespace ATL {

/*
 *
 *
 */
template<const unsigned char BitIndex = -1>
class Bit
{
public:
	template<typename T>
	inline static void Set(T& target)
	{
		target |= getMask<T>();
	}

	template<typename T>
	inline static void Set(T& target, bool value)
	{
		T mask = getMask<T>();

		// clear bit
		target &= ~mask;

		if (value)
		{
			// set bit
			target |= mask;
		}
	}

	template<typename T>
	inline static void Reset(T& target)
	{
		// clear bit
		target &= ~getMask<T>();
	}

	template<typename T>
	inline static void Toggle(T& target)
	{
		target ^= getMask<T>();
	}

	template<typename T>
	inline static bool IsTrue(T target)
	{
		return (target & getMask<T>()) > 0;
	}

	template<typename T>
	inline static bool IsFalse(T target)
	{
		return (target & getMask<T>()) == 0;
	}

protected:
	template<typename T>
	inline static T getMask()
	{
		static const T mask = 1 << BitIndex;
		return mask;
	}

private:
	Bit(){}
};


} // ATL

#endif //__BIT_H__