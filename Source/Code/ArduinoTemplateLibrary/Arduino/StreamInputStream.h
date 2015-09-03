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

#ifndef __STREAMINPUTSTREAM_H__
#define __STREAMINPUTSTREAM_H__

namespace ATL {
namespace IO {

/*
	This class is an adapter class to treat an Arduino Stream as an ATL InputStream.
	StreamT is a class with 'int read()' and 'int available()' (typical Arduino Stream).
 */
template<class StreamT>
class StreamInputStream
{
public:

	/*
		Call AttachInputStream afterwards.
	 */
	StreamInputStream() 
		: _stream(NULL)
	{}

	/*
		Initializes the stream.
	 */
	StreamInputStream(StreamT* serialStream)
	{
		AttachInputStream(serialStream);
	}

	/*
		Sets the ATL stream.
	 */
	inline void AttachInputStream(StreamT* serialStream)
	{
		_stream = serialStream;
	}

	/*
		Returns the number of bytes that are available in the stream.
	 */
	unsigned int getLength() const
	{
		if (_stream == NULL) return 0;

		return _stream->available();
	}

	/*
		Removes all content from the stream.
	 */
	void Clear()
	{
		if (_stream == NULL) return;

		while(_stream->read() != -1);
	}

	/*
		Reads one byte from the stream.
		Returns the byte read in the lsb (up to 9 bits). 
		If -1 is returned, no data was available or an error occurred.
	 */
	int Read()
	{
		if (_stream == NULL) return -1;

		return _stream->read();
	}

private:
	StreamT* _stream;
};

}} // ATL::IO

#endif //__STREAMINPUTSTREAM_H__