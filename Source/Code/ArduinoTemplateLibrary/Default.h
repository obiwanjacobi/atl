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

#ifndef __DEFAULT_H__
#define __DEFAULT_H__

namespace ATL {

    /** Static default values of T;
     *  \tparam T is the type to get the default value for.
     */
    template<typename T>
    class Default
    {
    public:
        /** A statically initialized default value of T.
         *  Treat as read-only.
         */
        static T DefaultOfT;
    };

    template<typename T>
    T Default<T>::DefaultOfT;


} // ATL

#endif //__DEFAULT_H__
