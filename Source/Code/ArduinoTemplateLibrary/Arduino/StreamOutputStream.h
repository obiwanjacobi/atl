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

#ifndef __STREAMOUTPUTSTREAM_H__
#define __STREAMOUTPUTSTREAM_H__

#include <stddef.h>
#include <stdint.h>

namespace ATL {

/*
	This class is an adapter class to treat an Arduino Stream as an ATL OutputStream.
	StreamT is a class with 'void write()' and 'void flush()' (typical Arduino Stream).
 */
template<class StreamT>
class StreamOutputStream
{
public:

	/*
		Call AttachInputStream afterwards.
	 */
	StreamOutputStream() 
		: _stream(NULL)
	{}

	/*
		Initializes the stream.
	 */
	StreamOutputStream(StreamT* serialStream)
	{
		AttachOutputStream(serialStream);
	}

	/*
		Sets the ATL stream.
	 */
	inline void AttachOutputStream(StreamT* serialStream)
	{
		_stream = serialStream;
	}

	/*
		Returns the number of bytes that are available in the stream.
	 */
	uint8_t getLength() const
	{
		if (_stream == NULL) return 0;

		return 0;
	}

	/*
		Removes all content from the stream.
	 */
	void Flush()
	{
		if (_stream == NULL) return;

		_stream->flush();
	}

	/*
		Writes one byte to the stream.
	 */
	void Write(uint8_t data)
	{
		if (_stream == NULL) return;

		_stream->write(data);
	}

private:
	StreamT* _stream;
};

} // ATL

#endif //__STREAMOUTPUTSTREAM_H__