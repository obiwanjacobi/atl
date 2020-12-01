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

#ifndef __RANGE_H__
#define __RANGE_H__

namespace ATL {

    /** The Range class contains 2 values for which in- and out of range checks can be performed.
     *  \tparam T is the datatype of the values.
     */
    template<typename T>
    class Range
    {
    public:
        /** Constructs the instance.
         */
        Range()
        {
        }

        /** Constructs an initialized instance.
         *  \param begin is the begin-value of the range.
         *  \param end is the end-value of the range.
         */
        Range(T begin, T end)
        {
            Begin = begin;
            End = end;
        }

        /** The begin-value of the range. */
        T Begin;
        /** The end-value of the range. */
        T End;

        /** Indicates if a value lies within range.
         *  The method compensates for non-normalized ranges and tests inclusive.
         *  \param value is the value to test.
         *  \return Returns true if the value lies within range.
         */
        bool IsInRange(const T value) const
        {
            if (Begin > End)
            {
                return (End <= value && value <= Begin);
            }

            return (Begin <= value && value <= End);
        }

        /** May swap the Begin and End field values in order to
         *  ensure that Begin is smaller than End.
         */
        void Normalize()
        {
            if (Begin > End)
            {
                T temp = End;
                End = Begin;
                Begin = temp;
            }
        }

        /** Indicates if the Begin value is smaller than the End value.
         *  \return Returns true if this is so.
         */
        inline bool IsNormalized() const
        {
            return (End >= Begin);
        }

        /** Adjusts the inoutValue to ensure its value does not lie outside the range.
         *  Make sure the Range is normalized.
         *  \param inoutValue is the value to clip.
         */
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