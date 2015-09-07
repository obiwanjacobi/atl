/*
Arduino Template Library http://atl.codeplex.com
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

#include "Array.h"
#include "Collection.h"
#include "Control.h"


namespace ATL {

template<const unsigned char MaxItems>
class ControlContainer : public Collection<Array<Control*, MaxItems> >
{
	typedef Collection<Array<Control*, MaxItems> > BaseT;

public:
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
};


} // ATL

#endif //__CONTROLCONTAINER_H__