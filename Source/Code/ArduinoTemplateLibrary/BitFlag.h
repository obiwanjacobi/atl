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

#ifndef __BITFLAG_H__
#define __BITFLAG_H__

#include <stdint.h>

#ifndef CHAR_BITS
#define CHAR_BITS 8
#endif

namespace ATL {

    /** Manipulates a single bit in a variable.
     *  The BitFlag class has similar functionality as the Bit class.
     *  BitFlag is a static class, meaning that no instance can be constructed.
     *  All methods are called like `BitFlag::Set(myVar, 2);` which would set bit2 in myVar.
     *  Use BitFlag instead of Bit when the bitIndex is dynamic/only known at runtime. 
     *  Bit is slightly more optimal when the bitIndex is known at compile time (hard-coded).
     */
    class BitFlag
    {
    public:
        /** Sets (true) the bit at bitIndex in target.
         *  \tparam T the data type of the target variable.
         *  \param target the variable that will be changed.
         *  \param bitIndex is the zero-based index where the value bits are stored.
         */
        template<typename T>
        inline static void Set(T& target, const uint8_t bitIndex)
        {
            if (bitIndex > getMaxBits<T>()) return;

            target |= BitToMask<T>(bitIndex);
        }

        /** Sets the bit at bitIndex in target to the specified value.
         *  \tparam T the data type of the target variable.
         *  \param target the variable that will be changed.
         *  \param bitIndex is the zero-based index where the value bits are stored.
         *  \param value is the value to be stored.
         */
        template<typename T>
        inline static void Set(T& target, const uint8_t bitIndex, bool value)
        {
            if (bitIndex > getMaxBits<T>()) return;

            T mask = BitToMask<T>(bitIndex);

            // clear bit
            target &= ~mask;

            if (value)
            {
                // set bit
                target |= mask;
            }
        }

        /** Resets (false) the bit at bitIndex in target.
         *  \tparam T the data type of the target variable.
         *  \param target the variable that will be changed.
         *  \param bitIndex is the zero-based index where the value bits are stored.
         */
        template<typename T>
        inline static void Reset(T& target, const uint8_t bitIndex)
        {
            if (bitIndex > getMaxBits<T>()) return;

            // clear bit
            target &= ~BitToMask<T>(bitIndex);
        }

        /** Toggles (inverts) the bit at bitIndex in target.
         *  \tparam T the data type of the target variable.
         *  \param target the variable that will be changed.
         *  \param bitIndex is the zero-based index where the value bits are stored.
         */
        template<typename T>
        inline static void Toggle(T& target, const uint8_t bitIndex)
        {
            if (bitIndex > getMaxBits<T>()) return;

            target ^= BitToMask<T>(bitIndex);
        }

        /** Indicates if the bit at bitIndex in target is set (true).
         *  \tparam T the data type of the target variable.
         *  \param target the variable that stores the bit value.
         *  \param bitIndex is the zero-based index where the value bits are stored.
         *  \return Returns true if the bit is set.
         */
        template<typename T>
        inline static bool IsTrue(T target, const uint8_t bitIndex)
        {
            if (bitIndex > getMaxBits<T>()) return false;

            return (target & BitToMask<T>(bitIndex)) > 0;
        }

        /** Indicates if the bit at bitIndex in target is reset (false).
         *  \tparam T the data type of the target variable.
         *  \param target the variable that stores the bit value.
         *  \param bitIndex is the zero-based index where the value bits are stored.
         *  \return Returns true if the bit is reset.
         */
        template<typename T>
        inline static bool IsFalse(T target, const uint8_t bitIndex)
        {
            if (bitIndex > getMaxBits<T>()) return false;

            return (target & BitToMask<T>(bitIndex)) == 0;
        }

        /** Retrieves the maximum number of bits that will fit into T.
         *  \tparam T the data type of the target variable.
         *  \return Returns the maximum number of bit positions.
         */
        template<typename T>
        inline static uint8_t getMaxBits()
        {
            return (sizeof(T) * CHAR_BITS);
        }

    protected:
        /** Calculates the bit mask for the bitIndex bit.
         *  \tparam T the data type of the target variable.
         *  \param bitIndex is the zero-based index a mask is constructed for.
         *  \return Returns a value with the BitIndex'th bit set.
         */
        template<typename T>
        inline static T BitToMask(const uint8_t bitIndex)
        {
            return 1 << bitIndex;
        }

    private:
        BitFlag()
        { }
    };


} // ATL

#endif //__BITFLAG_H__