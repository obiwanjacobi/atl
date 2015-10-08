#ifndef __USARTOUTPUTSTREAM_H__
#define __USARTOUTPUTSTREAM_H__

#include "../RingBuffer.h"

namespace ATL {
namespace MCU {

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
     *  \param data the byte that is written to the output stream.
     */
    inline void Write(uint8_t data)
    {
        _buffer.Write(data);
		BaseT::setEnableWantDataInterrupt(true);
    }
	
	inline void OnWantDataInterrupt()
	{
		if (_buffer.getLength())
		{
			// write the next byte from buffer
			BaseT::WriteInternal(_buffer.Read());
		}
		else
		{
			// Turn off interrupt when no data is available.
			BaseT::setEnableWantDataInterrupt(false);
		}
	}
	
	inline uint16_t getBufferSize() const
	{
		return BufferSize;
	}
	
private:
	RingBuffer<T, BufferSize> _buffer;
};  

}}	// ATL::MCU

#endif // __USARTOUTPUTSTREAM_H__