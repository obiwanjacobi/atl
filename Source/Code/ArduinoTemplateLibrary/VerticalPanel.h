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

#ifndef __VERTICALPANEL_H__
#define __VERTICALPANEL_H__

#include <stddef.h>
#include <stdint.h>
#include "NavigationController.h"
#include "Control.h"
#include "PanelControlContainer.h"


namespace ATL {

    /** The VerticalPanel implements a Control Panel where controls are lined up vertically.
     *  It overrides the `OnNavigationCommand()` and `Display()` methods to implement its behavior.
     *  \tparam MaxItems is the maximum number of Controls in the Panel.
     */
    template<const uint8_t MaxItems>
    class VerticalPanel : public PanelControlContainer < MaxItems >
    {
        typedef PanelControlContainer<MaxItems> BaseT;

    public:
        /** Constructs the instance with an option position.
         *  \param pos is the position relative to its siblings.
         */
        VerticalPanel(uint8_t pos = 0)
            : BaseT(pos)
        { }

        /** Routes the command to its BaseT and implements Panel navigation.
         *  If the navCmd is not handled by BaseT the Panel adjusts the current (selected) control
         *  on the `Up` and `Down` commands.
         *  \param navCmd is the navigation command.
         *  \return Returns true when the command was handled, otherwise false.
         */
        virtual bool OnNavigationCommand(NavigationCommands navCmd)
        {
            switch (navCmd)
            {
            case NavigationCommands::Up:
                return BaseT::SetPreviousInputControl();
            case NavigationCommands::Down:
                return BaseT::SetNextInputControl();
            default:
                break;
            }

            return BaseT::OnNavigationCommand(navCmd);
        }

        /** Displays all the visible controls in the Panel.
         *  If the mode is Control::modeCursor it is routed to the BaseT implementation -
         *  where Panel will route it to the current (selected) control.
         *  For normal display mode the BaseT is not called and all (visible) controls will be called after their positions have be set.
         *  \param output is a pointer to the display writer that can be used to output and position text.
         *  \param mode is the display mode and results in different behavior.
         */
        virtual void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal)
        {
            if (mode == ControlDisplayMode::Cursor)
            {
                BaseT::Display(output, mode);
                return;
            }

            for (uint8_t i = 0; i < BaseT::getCount(); i++)
            {
                Control* ctrl = BaseT::GetAt(i);

                if (ctrl->getIsVisible())
                {
                    output->GoTo(ctrl->getPosition(), 0);
                    ctrl->Display(output, mode);
                }
            }
        }
    };


} // ATL

#endif //__VERTICALPANEL_H__