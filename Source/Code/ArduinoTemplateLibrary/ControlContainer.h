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

#ifndef __CONTROLCONTAINER_H__
#define __CONTROLCONTAINER_H__

#include <stddef.h>
#include <stdint.h>
#include "FixedArray.h"
#include "Collection.h"
#include "Control.h"


namespace ATL {

    /** The ControlContainer represents a collection of `Control`s.
     *  It uses Collection and FixedArray to implement the collection.
     *  \tparam MaxItems is the maximum number of controls in the container.
     */
    template<const uint8_t MaxItems>
    class ControlContainer : public Collection<FixedArray<Control*, MaxItems> >
    {
        typedef Collection<FixedArray<Control*, MaxItems> > BaseT;

    public:
        /** Retrieves the Control that is next to the currentCtrl.
         *  \param currentCtrl is a pointer to the Control to use as reference.
         *  \param type is the type of Control to look for. Uses Control::DynamicCast.
         *  \return Returns NULL if no suitable Control (type) could be found.
         */
        Control* getNext(Control* currentCtrl, ControlTypes type = typeControl) const
        {
            int8_t index = BaseT::IndexOf(currentCtrl);

            if (index != -1)
            {
                index++;
            }
            else if (BaseT::getCount() > 0)
            {
                index = 0;
            }

            while (index >= 0 && index < BaseT::getCount())
            {
                Control* ctrl = Control::DynamicCast(BaseT::GetAt(index), type);

                if (ctrl != NULL) return ctrl;

                index++;
            }

            return NULL;
        }

        /** Retrieves the Control that is before the currentCtrl.
         *  \param currentCtrl is a pointer to the Control to use as reference.
         *  \param type is the type of Control to look for. Uses Control::DynamicCast.
         *  \return Returns NULL if no suitable Control (type) could be found.
         */
        Control* getPrevious(Control* currentCtrl, ControlTypes type = typeControl) const
        {
            int8_t index = BaseT::IndexOf(currentCtrl);

            if (index != -1)
            {
                index--;
            }
            else if (BaseT::getCount() > 0)
            {
                index = BaseT::getCount() - 1;
            }

            while (index >= 0 && index < BaseT::getCount())
            {
                Control* ctrl = Control::DynamicCast(BaseT::GetAt(index), type);

                if (ctrl != NULL) return ctrl;

                index--;
            }

            return NULL;
        }

        /** Overrides Collection::Add to disallow NULL pointer in the collection.
         *  \param control is the control to add. If NULL nothing happens.
         */
        inline void Add(Control* control)
        {
            if (control == NULL) return;

            BaseT::Add(control);
        }
    };


} // ATL

#endif //__CONTROLCONTAINER_H__