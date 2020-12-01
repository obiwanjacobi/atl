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

#ifndef __USARTOUTPUTSTREAM_H__
#define __USARTOUTPUTSTREAM_H__

#include "../RingBuffer.h"

namespace ATL {
namespace MCU {

/** The UsartOutputStream can be constructed around the UsartTransmist class
 *  to add buffered and interrupt based data transmission.
 *  \tparam BaseT is used as base class and is the UsartTransmit class and implements
 *  `void Flush()`
 *  `void setEnableWantDataInterrupt(bool)`
 *  `void Close()`
 *  `void WriteInternal(int16_t)` (protected)
 *  \tparam BufferSize is the number of 'T' to allocate.
 *  \tparam T is the data type to use. For 9 data bits reception int16_t should be used.
 *  By default uint8_t is used.
 */
template<typename BaseT, const uint16_t BufferSize, typename T = uint8_t>
class UsartOutputStream : public BaseT
{
public:
    /** Returns the number of bytes in the stream.
     *  \return Returns 0 (zero) when empty.
     */
    inline uint8_t getLength() const
    {
        return _buffer.getLength();
    }

    /** Removes all content from the output stream.
     */
    inline void Flush()
    {
        _buffer.Clear();
        BaseT::Flush();
    }

    /** Writes one byte to the stream.
     *  Also turns on the interrupt.
     *  \param data the byte that is written to the output stream.
     */
    inline void Write(uint8_t data)
    {
        _buffer.Write(data);
        BaseT::setEnableAcceptDataInterrupt(true);
    }
    
    /** Call this method from the `ISR(USARTn_UDRE_vect)` interrupt handler.
     *  May turn of the interrupt if the buffer is empty.
     *  Not meant to be called from regular code.
     */
    inline void OnAcceptDataInterrupt()
    {
        if (_buffer.getLength())
        {
            // write the next byte from buffer
            BaseT::WriteInternal(_buffer.Read());
        }
        else
        {
            // Turn off interrupt when no data is available.
            BaseT::setEnableAcceptDataInterrupt(false);
        }
    }
    
    /** Retrieves the buffer size used for storing transmit data.
     *  \return Returns the BufferSize template parameter.
     */
    inline uint16_t getBufferSize() const
    {
        return BufferSize;
    }
    
    /** Closes the output stream and transmitter.
     *  Data still in the buffer is lost.
     */
    inline void Close()
    {
        _buffer.Clear();
        BaseT::Close();
    }

private:
    RingBuffer<T, BufferSize> _buffer;
};  

}}	// ATL::MCU

#endif // __USARTOUTPUTSTREAM_H__