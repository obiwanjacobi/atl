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

#ifndef __DIGITALINPUT_H__
#define __DIGITALINPUT_H__

namespace ATL {

    /** The DigitalInput class maintains the last read value to indicate change.
     *  The DigitalInput class derives from BaseT.
     *  \tparam BaseT is DigitalInputPin or a class that implements `bool Read()`.
     */
    template<class BaseT>
    class DigitalInput : public BaseT
    {
    public:
        /** Constructs an instance.
         */
        DigitalInput() 
            : _value(false)
        { }

        /** Reads the value from the DigitalInputPin.
         *  This method can be called repeatedly.
         *  \return Returns true when a new value was read - it is NOT the value itself.
         */
        bool Read()
        {
            bool value = BaseT::Read();

            if (_value != value)
            {
                _value = value;
                return true;
            }

            return false;
        }

        /** Returns the value that was last read by `Read()`.
         *  \return Returns the value.
         */
        bool getValue() const
        {
            return _value;
        }

    private:
        bool _value;
    };

} // ATL

#endif //__DIGITALINPUT_H__