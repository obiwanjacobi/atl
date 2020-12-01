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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stddef.h>
#include <stdint.h>
#include "EnumScope.h"

namespace ATL {

    /** Intended t give an indication on the ComponentId value ranges.
     *  All ComponentIds 0x00-0x7F are reserved. Start your custom ComponentIds
     *  at 0x80-0xFF.
     */
    BeginEnum(AtlComponentIds)
    {
        AtlReservedStart = 0x00,
        AtlReservedEnd = 0x7F,
        AtlUserStart = 0x80,
        AtlUserEnd = 0xFF,
    }
    EndEnum(AtlComponentIds)

    /** Indicates the debug logging level.
     *  Do not use Off.
     */
    BeginEnum(DebugLevel)
    {
        /** Do not use. */
        Off,
        /** Indicates a critical error in the system. */
        Critical,
        /** Indicates an error in the system. */
        Error,
        /** Indicates a warning message. */
        Warning,
        /** Indicates a informational message. */
        Info,
        /** Indicates a verbose or debug message. */
        Verbose
    }
    EndEnum(DebugLevel)


#if defined(DEBUG) || defined(_DEBUG)

    // implement this method in your own code and route the message to the desired output.
    void AtlDebugWrite(const char* message) __attribute__((weak));

    // Optionally implement this method in your own code and determine what debug level and components are debugged.
    bool AtlDebugLevel(const uint8_t componentId, DebugLevel debugLevel) __attribute__((weak));

    /** The Debug class allows conditionally writing messages from code to an unspecified target.
     *  The Debug class is a static class and cannot be instantiated.
     *  \tparam ComponentId is used as a component id for filtering debug log writes.
     */
    template<const uint8_t ComponentId>
    class Debug
    {
    public:
        /** Logs the message to the debug target.
         *  \tparam debugLevel indicates for which level the message is intended.
         *  Do not use `DebugLevel::Off`.
         *  \param message is the message text to write.
         */
        template<const DebugLevel::type debugLevel>
        inline static void Log(const char* message)
        {
            if (AtlDebugWrite == NULL) return;
            if (!CanLog<debugLevel>()) return;
            AtlDebugWrite(message);
        }

        /** Indicates if a message to the debug target for the specified ComponentId and debugLevel.
         *  \tparam debugLevel indicates for which level the message is intended.
         *  Do not use `DebugLevel::Off`.
         *  \return Returns true if logging is enabled.
         */
        template<const DebugLevel::type debugLevel >
        inline static bool CanLog()
        {
            if (AtlDebugLevel == NULL) return true;
            return AtlDebugLevel(ComponentId, debugLevel);
        }

    private:
        Debug() { }
    };

#else

    /** The Debug class for release builds is an empty class.
     *  The Debug class is a static class and cannot be instantiated.
     *  \tparam ComponentId is used as a component id for filtering debug log writes.
     */
    template<const uint8_t ComponentId>
    class Debug
    {
    public:
        /** Does nothing.
         *  \tparam debugLevel indicates for which level the message is intended.
         *  Do not use `DebugLevel::Off`.
         *  \param message is not used.
         */
        template<const DebugLevel::type debugLevel>
        inline static void Log(const char* /*message*/) {}

        /** Always returns false.
         *  \tparam debugLevel indicates for which level the message is intended.
         *  Do not use `DebugLevel::Off`.
         *  \return Returns false.
         */
        template<const DebugLevel::type debugLevel >
        inline static bool CanLog() { return false; }

    private:
        Debug() { }
    };

#endif  //DEBUG|_DEBUG

} // ATL

#endif //__DEBUG_H__