/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2013 All Rights Reserved

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

namespace ATL {
namespace IO {

// The BufferedInputStream implements an abstract InputStream by using a circular buffer (RingBuffer).
/*
	BaseT is the class of a RingBuffer implementation: 
		unsigned int [IO.Stream]getLength(); 
		int [IO.InputStream.]Read(); 
*/
template<class BaseT>
class BufferedInputStream : public BaseT
{
public:
	// adapts the Read method to always check for length.
	int Read()
	{
		if(BaseT::getLength() == 0)
		{
			return -1;
		}

		return (int)BaseT::Read();
	}
};

}} // ATL.IO

#endif //__BUFFEREDINPUTSTREAM_H__