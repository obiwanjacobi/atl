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

#ifndef __PANELCONTROLCONTAINER_H__
#define __PANELCONTROLCONTAINER_H__

#include <stddef.h>
#include <stdint.h>
#include "ControlContainer.h"
#include "InputControl.h"
#include "Panel.h"

namespace ATL {


    /** The PanelControlContainer abstract class manages a collection of Controls.
     *  \tparam MaxItems is the maximum number of Controls in the container.
     */
    template<const uint8_t MaxItems>
    class PanelControlContainer : public Panel,
                                  public ControlContainer<MaxItems>
    {
        typedef ControlContainer<MaxItems> BaseT;

    public:
        /** Assigns the first InputControl in the container to be the current control (Panel).
         *  \return Returns true if successful.
         */
        bool SetFirstInputControl()
        {
            InputControl* ctrl = (InputControl*)BaseT::getNext(NULL, ControlTypes::InputControl);
            if (ctrl != NULL)
            {
                setCurrentControl(ctrl);
                return true;
            }

            return false;
        }

        /** Assigns the next InputControl (relative to the current current-control) in the container to be the current control (Panel).
         *  \return Returns true if successful.
         */
        bool SetNextInputControl()
        {
            InputControl* ctrl = (InputControl*)BaseT::getNext(getCurrentControl(), ControlTypes::InputControl);
            if (ctrl != NULL)
            {
                setCurrentControl(ctrl);
                return true;
            }

            return false;
        }

        /** Assigns the previous InputControl (relative to the current current-control) in the container to be the current control (Panel).
         *  \return Returns true if successful.
         */
        bool SetPreviousInputControl()
        {
            InputControl* ctrl = (InputControl*)BaseT::getPrevious(getCurrentControl(), ControlTypes::InputControl);
            if (ctrl != NULL)
            {
                setCurrentControl(ctrl);
                return true;
            }

            return false;
        }

    protected:
        /** For derived classes.
         *  \param pos is the optional control position.
         */
        PanelControlContainer(uint8_t pos = 0)
            : Panel(pos)
        { }
    };


} // ATL

#endif //__PANELCONTROLCONTAINER_H__