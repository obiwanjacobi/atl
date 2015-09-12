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

#ifndef __PAGECONTROLLER_H__
#define __PAGECONTROLLER_H__

#include <stddef.h>
#include <stdint.h>

#include "NavigationController.h"
#include "ControlContainer.h"
#include "Page.h"

namespace ATL {


	template<const uint8_t LinesPerPage, const uint8_t MaxPages>
class PageController : public ControlContainer<MaxPages>,
                       public NavigationController
{

public:
	typedef Page<LinesPerPage> PageT;

	inline PageT* getCurrentPage() const
	{
		return _currentPage;
	}

private:
	PageT* _currentPage;
};


} // ATL

#endif //__PAGECONTROLLER_H__