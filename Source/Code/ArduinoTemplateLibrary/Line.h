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

#ifndef __LINE_H__
#define __LINE_H__

#include <stddef.h>
#include <stdint.h>

#include "Control.h"
#include "HorizontalPanel.h"

namespace ATL {

template<const uint8_t MaxItems>
class Line : public HorizontalPanel<MaxItems>
{
	typedef HorizontalPanel<MaxItems> BaseT;

public:
	Line() { }

	Line(Control* control1)
	{
		if (control1 != NULL) BaseT::Add(control1);
	}

	Line(Control* control1, Control* control2)
	{
		if (control1 != NULL) BaseT::Add(control1);
		if (control2 != NULL) BaseT::Add(control2);
	}

	Line(Control* control1, Control* control2, Control* control3)
	{
		if (control1 != NULL) BaseT::Add(control1);
		if (control2 != NULL) BaseT::Add(control2);
		if (control3 != NULL) BaseT::Add(control3);
	}

	Line(Control* control1, Control* control2, Control* control3, Control* control4)
	{
		if (control1 != NULL) BaseT::Add(control1);
		if (control2 != NULL) BaseT::Add(control2);
		if (control3 != NULL) BaseT::Add(control3);
		if (control4 != NULL) BaseT::Add(control4);
	}

	Line(Control* control1, Control* control2, Control* control3, Control* control4, Control* control5)
	{
		if (control1 != NULL) BaseT::Add(control1);
		if (control2 != NULL) BaseT::Add(control2);
		if (control3 != NULL) BaseT::Add(control3);
		if (control4 != NULL) BaseT::Add(control4);
		if (control5 != NULL) BaseT::Add(control5);
	}
};


} // ATL

#endif //__LINE_H__