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

#ifndef __NAVIGATIONCONTROLLER_H__
#define __NAVIGATIONCONTROLLER_H__

#include "EnumScope.h"

namespace ATL {

    /** Enumerates the navigation commands for the UI framework.
     */
    BeginEnum(NavigationCommands) //: uint8_t
    {
        /** Not a navigation command. */
        None,
        /** Navigate Up. */
        Up,
        /** Navigate Down. */
        Down,
        /** Navigate Left. */
        Left,
        /** Navigate Right. */
        Right,
        /** Enter edit mode. */
        Enter,
        /** Exit edit mode. */
        Exit
    }
    EndEnum(NavigationCommands)

    /** The NavigationController class is a template for Controls that receive input stimuli.
     *  See also InputControl.
     */
    class NavigationController
    {
    public:
        /** Called when an input event has happened and is translated into a navigation command.
         *  \param navCmd is the navigation command.
         *  \return The return value indicates if the command was handled. Returning false may cause
         *  the navigation command to be routed to other controls.
         */
        virtual bool OnNavigationCommand(NavigationCommands /*navCmd*/)
        {
            return false;
        }
    };


} // ATL

#endif //__NAVIGATIONCONTROLLER_H__