#ifndef __OUTPUTPINTASK_H__
#define __OUTPUTPINTASK_H__

#include <ATL_IO.h>
#include <ATL_Process.h>

using namespace ATL;

// IdentifiableObject::getId is called by the TimeoutTask
template <unsigned char BoardPin>
class OutputPinTask : public IdentifiableObject<DigitalOutputPin<BoardPin> >
{
  typedef IdentifiableObject<DigitalOutputPin<BoardPin> > BaseT;
  
protected:
  // called by the TimeoutTask
  inline void OnTimeout()
  {
    BaseT::Toggle();
  }
};

#endif //__OUTPUTPINTASK_H__
