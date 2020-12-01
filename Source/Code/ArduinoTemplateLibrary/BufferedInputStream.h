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

#ifndef __BUFFEREDINPUTSTREAM_H__
#define __BUFFEREDINPUTSTREAM_H__

#include <stdint.h>

namespace ATL {

    /** The BufferedInputStream implements an abstract InputStream by using a circular buffer (RingBuffer).
     *  This class derives from the BaseT type.
     *	\tparam BaseT is the RingBuffer implementation: 
     *  `unsigned uint8_t getLength();`
     *  `int Read();`
     */
    template<class BaseT>
    class BufferedInputStream : public BaseT
    {
    public:
        /** Adapts the Read method to always check for length.
         *  \return Returns -1 if no data is available.
         */
        int16_t Read()
        {
            if(BaseT::getLength() == 0)
            {
                return -1;
            }

            return (int16_t)BaseT::Read();
        }
    };

} // ATL

#endif //__BUFFEREDINPUTSTREAM_H__