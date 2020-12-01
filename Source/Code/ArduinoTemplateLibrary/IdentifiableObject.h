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

#ifndef __IDENTIFIABLEOBJECT_H__
#define __IDENTIFIABLEOBJECT_H__

namespace ATL {

    /** Adds an Id to any class.
     *  Typically used by the Task macros and the Delays class to identify the owner of registered delays.
     *  \tparam BaseT is for convenience and not used by this class.
     */
    template<class BaseT>
    class IdentifiableObject : public BaseT
    {
    public:
        /** Returns an id based on the this pointer.
         *  \return Returns a unique id.
         */
        inline uint16_t getId() const
        {
            return (uint16_t)this;
        }
    };

} // ATL

#endif //__IDENTIFIABLEOBJECT_H__