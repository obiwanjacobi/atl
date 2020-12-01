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

#ifndef __VALUE_H__
#define __VALUE_H__

namespace ATL {

    // \todo Not happy with the name ValueContainer.
    // Its more a value comparer or validator.
    // See also Range - may want to derive from that.
    template <typename T>
    class ValueContainer
    {
    public:
        enum Mode
        {
            None,
            Single,
            Range,
            Any,
        };

        ValueContainer()
        {
            SetNone();
        }

        ValueContainer(T value)
        {
            SetSingle(value);
        }

        ValueContainer(T begin, T end)
        {
            SetRange(begin, end);
        }

        inline void SetSingle(T value)
        {
            _mode = Single;
            _begin = value;
            _end = value;
        }

        inline void SetRange(T begin, T end)
        {
            _mode = Range;
            _begin = begin;
            _end = end;
        }

        inline void SetAny()
        {
            _mode = Any;
        }

        inline void SetNone()
        {
            _mode = None;
        }

        inline Mode getMode() const { return _mode; }
        inline T getValue() const { return _begin; }
        inline T getBegin() const { return _begin; }
        inline T getEnd() const { return _end; }

        bool IsInRange(T value) const
        {
            if (_mode == None) return false;
            if (_mode == Any) return true;

            if (_begin > _end)
            {
                return (_end <= value && value <= _begin);
            }

            return (_begin <= value && value <= _end);
        }

        void Normalize()
        {
            if (_begin > _end)
            {
                T temp = _end;
                _end = _begin;
                _begin = temp;
            }
        }

    private:
        Mode _mode;
        T _begin;
        T _end;
    };

} //ATL

#endif //__VALUE_H__