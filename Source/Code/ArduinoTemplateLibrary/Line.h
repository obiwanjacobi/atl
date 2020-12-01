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

#ifndef __LINE_H__
#define __LINE_H__

#include <stddef.h>
#include <stdint.h>
#include "Control.h"
#include "HorizontalPanel.h"

namespace ATL {

    /** The Line class represent a single line on a display that may contain multiple Controls.
     *  The Line class derives from the HorizontalPanel class.
     *  \tparam MaxItems is the maximum number of Controls on the Line.
     */
    template<const uint8_t MaxItems>
    class Line : public HorizontalPanel<MaxItems>
    {
        typedef HorizontalPanel<MaxItems> BaseT;

    public:
        /** Constructs the instance.
         *  Controls have to be added with the Add method.
         */
        Line()
        { }

        /** Constructs the instance.
         *  Controls can be added with the Add method.
         *  \param control1 is the first control.
         */
        Line(Control* control1)
        {
            if (control1 != NULL) BaseT::Add(control1);
        }

        /** Constructs the instance.
         *  Controls can be added with the Add method.
         *  \param control1 is the first control.
         *  \param control2 is the second control.
         */
        Line(Control* control1, Control* control2)
        {
            if (control1 != NULL) BaseT::Add(control1);
            if (control2 != NULL) BaseT::Add(control2);
        }

        /** Constructs the instance.
         *  Controls can be added with the Add method.
         *  \param control1 is the first control.
         *  \param control2 is the second control.
         *  \param control3 is the third control.
         */
        Line(Control* control1, Control* control2, Control* control3)
        {
            if (control1 != NULL) BaseT::Add(control1);
            if (control2 != NULL) BaseT::Add(control2);
            if (control3 != NULL) BaseT::Add(control3);
        }

        /** Constructs the instance.
         *  Controls can be added with the Add method.
         *  \param control1 is the first control.
         *  \param control2 is the second control.
         *  \param control3 is the third control.
         *  \param control4 is the fourth control.
         */
        Line(Control* control1, Control* control2, Control* control3, Control* control4)
        {
            if (control1 != NULL) BaseT::Add(control1);
            if (control2 != NULL) BaseT::Add(control2);
            if (control3 != NULL) BaseT::Add(control3);
            if (control4 != NULL) BaseT::Add(control4);
        }

        /** Constructs the instance.
         *  Controls can be added with the Add method.
         *  \param control1 is the first control.
         *  \param control2 is the second control.
         *  \param control3 is the third control.
         *  \param control4 is the fourth control.
         *  \param control5 is the fifth control.
         */
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