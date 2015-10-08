
#ifndef __USARTINPUTSTREAM_H__
#define __USARTINPUTSTREAM_H__

#include "../RingBuffer.h"

namespace ATL {
namespace MCU {

template<typename BaseT, const uint16_t BufferSize, typename T = uint8_t>
class UsartInputStream : public BaseT
{
public:
	/** Returns the number of bytes that are available in the stream.
     *  \return Returns 0 (zero) when empty.
     */
    uint16_t getLength() const
    {
        return _buffer.getLength();
    }

    /** Removes all content from the stream.
     *  Keeps reading the input stream until there is nothing left.
     */
    void Clear()
    {
		BaseT::Flush();
		_buffer.Clear();
    }

    /** Reads one byte from the stream.
     *  \return Returns the byte read in the lsb (up to 9 bits). 
     *  If -1 is returned, no data was available or an error occurred.
     */
    int16_t Read()
    {
        if (_buffer.getLength() > 0)
		{
			return _buffer.Read();
		}
		
		BaseT::setEnableIsCompleteInterrupt(true);
		return -1;
    }
	
	inline void OnIsCompleteInterrupt()
	{
		UsartReceiveResult result = BaseT::getResult();
		int16_t data = BaseT::ReadInternal();
		
		if (result == UsartReceiveResult::Success)
			_buffer.Write((T)data);
	}
	
	inline uint16_t getBufferSize() const
	{
		return BufferSize;
	}
	
private:
	RingBuffer<T, BufferSize> _buffer;
};

}}	// ATL::MCU

#endif // __USARTINPUTSTREAM_H__