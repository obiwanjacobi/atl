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

#ifndef __PUSHBUTTON_H__
#define __PUSHBUTTON_H__

#include "BitArray.h"
#include "Delays.h"
#include "Task.h"

namespace ATL {

    /** The different states the PushButton can be in.
     */
    enum ButtonStates
    {
        /** Button state not initialized / unknown. */
        stateUnknown,
        /** Button contact is open / not pushed. */
        stateOpen,
        /** Button contact is closed / pushed. */
        stateClosed,
        /** Button contact remains closed / pushed (holdTimeout). */
        stateHold,
        /** Button state sensing is pending for debounce (debounceTimeout). */
        statePending,
    };


    namespace Implementation {

        // template with static converter function for reversed logic
        template<const bool ReversedLogic>
        struct ConvertBoolToButtonState
        {
            inline static ButtonStates Convert(bool value);
        };

        template<>
        struct ConvertBoolToButtonState<false>
        {
            inline static ButtonStates Convert(bool value)
            {
                return value ? stateClosed : stateOpen;
            }
        };

        template<>
        struct ConvertBoolToButtonState<true>
        {
            inline static ButtonStates Convert(bool value)
            {
                return value ? stateOpen : stateClosed;
            }
        };

    } // ATL::Implementation


    /** The PushButton class implements the logic for reading 'a tactile contact'.
     *  The class has a debounce timeout and also a timeout to detect holding the contact closed.
     *  It uses the Task macros to implement non-blocking timeout handling.
     *  \tparam BaseT is used as base class and implements:
     *  `bool Read()` (DigitalInputPin)
     *  `uint16_t getId()` (IdentifiableObject).
     *  \tparam DelaysT is the static class used to manage delay timeouts. See Delays.
     *  \tparam DebounceTimeout is the timeout for contact debounce in units used in DelaysT.
     *  \tparam HoldTimeout is the button contact closed timeout for entering stateHold.
     *  \tparam InverseValue is how a digital input value translates to button state:
     *  false => 0=stateOpen | 1=stateClosed (pull-down)
     *  true => 0=stateClosed | 1=stateOpen (pull-up)
     */
    template<class BaseT, typename DelaysT, 
        const uint32_t DebounceTimeout, const uint32_t HoldTimeout, 
        const bool InverseValue=false>
    class PushButton : public BaseT
    {
        // bit array indexes
#define CurrentStateIndex 0
#define PrevStateIndex 3
#define ButtonStateLength 3

    public:

        /** Call this method repeatedly (main loop).
         *  This method manages the state of the class.
         *  \return Returns true when the task is yielding.
         */
        Task_Begin(ScanButton)
        {
            SampleButtonState();

            // debounce
            if (DebounceButton())
            {
                Task_YieldUntil(WaitForDebounce());

                setPrevState(getState());
                setState(ConvertToButtonState(BaseT::Read()));
            }

            // hold
            if (getState() == stateClosed)
            {
                if(WaitForHold())
                {
                    setPrevState(getState());
                    setState(stateHold);
                }
            }
            else if (DelaysT::IsWaiting(BaseT::getId()))
            {
                DelaysT::Clear(BaseT::getId());
            }
        }
        Task_End

        /** Retrieves the current state of the push button.
         *  \return Returns the state.
         */
        inline ButtonStates getState() const
        {
            return (ButtonStates)_states.Get(CurrentStateIndex, ButtonStateLength);
        }

        /** Returns the DebounceTimeout template parameter.
         */
        inline uint32_t getDebounceTimeout() const
        {
            return DebounceTimeout;
        }

        /** Returns the HoldTimeout template parameter.
         */
        inline uint32_t getHoldTimeout() const
        {
            return HoldTimeout;
        }

        /** Returns the InverseValue template parameter.
         */
        inline bool getInverseValue() const
        {
            return InverseValue;
        }

    private:
        int16_t _task;
        BitArray<uint8_t> _states;

        inline void SampleButtonState()
        {
            ButtonStates newState = ConvertToButtonState(BaseT::Read());
            ButtonStates state = getState();

            // new state, but not in hold
            if (state != newState 
                && !(newState == stateClosed && state == stateHold)
                )
            {
                setPrevState(state);
                setState(newState);
            }
        }

        inline bool DebounceButton()
        {
            ButtonStates prevState = getPrevState();
            ButtonStates state = getState();

            // button changed (meaningful) states
            if (prevState != state 
                && state != stateHold
                && prevState != stateUnknown 
                && prevState != statePending
                )
            {
                DelaysT::Clear(BaseT::getId());
                setState(statePending);
                return true;
            }

            return false;
        }

        inline ButtonStates getPrevState() const
        {
            return (ButtonStates)_states.Get(PrevStateIndex, ButtonStateLength);
        }

        inline void setPrevState(ButtonStates state)
        {
            _states.Set(PrevStateIndex, state, ButtonStateLength);
        }

        inline void setState(ButtonStates state)
        {
            _states.Set(CurrentStateIndex, state, ButtonStateLength);
        }

        inline bool WaitForDebounce() const
        {
            return DelaysT::Wait(BaseT::getId(), getDebounceTimeout());
        }

        inline bool WaitForHold() const
        {
            return DelaysT::Wait(BaseT::getId(), getHoldTimeout());
        }

        inline static ButtonStates ConvertToButtonState(bool value)
        {
            return Implementation::ConvertBoolToButtonState<InverseValue>::Convert(value);
        }
    };

} // ATL

#endif //__PUSHBUTTON_H__