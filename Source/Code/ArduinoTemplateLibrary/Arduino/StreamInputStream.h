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

#ifndef __STREAMINPUTSTREAM_H__
#define __STREAMINPUTSTREAM_H__

#include <stddef.h>
#include <stdint.h>

namespace ATL {

    /** This class is an adapter class to treat an Arduino Stream as an ATL InputStream.
     *  The class protects against initializing it with NULL or not initializing it at all.
     *  \tparam StreamT is a class with `int read()` and `int available()` (typical Arduino Stream).
     */
    template<class StreamT>
    class StreamInputStream
    {
    public:

        /** Default ctor.
         *  Call AttachInputStream afterwards.
         */
        StreamInputStream() 
            : _stream(NULL)
        {}

        /** Initializes the stream.
         *  \param serialStream is a pointer to an Arduino stream.
         */
        StreamInputStream(StreamT* serialStream)
        {
            AttachInputStream(serialStream);
        }

        /** Sets the Arduino stream.
         *  \param serialStream is a pointer to an Arduino stream.
         */
        inline void AttachInputStream(StreamT* serialStream)
        {
            _stream = serialStream;
        }

        /** Returns the number of bytes that are available in the stream.
         *  \return Returns the number of bytes `available()`.
         */
        uint16_t getLength() const
        {
            if (_stream == NULL) return 0;

            return _stream->available();
        }

        /** Removes all content from the stream.
         *  Keeps reading the Arduino stream until there is nothing left.
         */
        void Clear()
        {
            if (_stream == NULL) return;

            while(_stream->read() != -1);
        }

        /** Reads one byte from the stream.
         *  \return Returns the byte read in the lsb (up to 9 bits). 
         *  If -1 is returned, no data was available or an error occurred.
         */
        int16_t Read()
        {
            if (_stream == NULL) return -1;

            return _stream->read();
        }

    private:
        StreamT* _stream;
    };

} // ATL

#endif //__STREAMINPUTSTREAM_H__