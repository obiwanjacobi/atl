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

#ifndef __PAGECONTROLLER_H__
#define __PAGECONTROLLER_H__

#include <stddef.h>
#include <stdint.h>
#include "NavigationController.h"
#include "PanelControlContainer.h"
#include "Page.h"

namespace ATL {

    /** The PageController class manages multiple pages and the transition of one page to another.
     *  \tparam LinesPerPage is the number of lines per page (must be the same for all pages).
     *  \tparam MaxPages is the maximum number of pages.
     */
    template<const uint8_t LinesPerPage, const uint8_t MaxPages>
    class PageController : public PanelControlContainer<MaxPages>
    {
        typedef PanelControlContainer<MaxPages> BaseT;

    public:
        /** The Page type. */
        typedef Page<LinesPerPage> PageT;

        /** Retrieves the current active page.
         *  \return Returns NULL when no active page is set.
         */
        inline PageT* getCurrentPage() const
        {
            return (PageT*)BaseT::getCurrentControl();
        }

        /** Navigates to a new page when `Up` or `Down` remain unhandled.
         *  \param navCmd is the navigation command.
         *  \return Returns false when the navCmd was not handled.
         */
        virtual bool OnNavigationCommand(NavigationCommands navCmd)
        {
            bool handled = BaseT::OnNavigationCommand(navCmd);

            if (handled) return true;

            switch (navCmd)
            {
            case Up:
                handled = TrySetPreviousPage();
                break;
            case Down:
                handled = TrySetNextPage();
                break;
            default:
                break;
            }

            return handled;
        }

        /** Attempts to set the first page.
         *  \return Returns true when successful.
         */
        inline bool TrySetFirstPage()
        {
            return BaseT::SetFirstInputControl();
        }

        /** Attempts to set the next page.
         *  \return Returns true when successful.
         */
        inline bool TrySetNextPage()
        {
            return BaseT::SetNextInputControl();
        }

        /** Attempts to set the previous page.
         *  \return Returns true when successful.
         */
        inline bool TrySetPreviousPage()
        {
            return BaseT::SetPreviousInputControl();
        }
    };


} // ATL

#endif //__PAGECONTROLLER_H__