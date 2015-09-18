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

#ifndef __TEXTCONTROL_H__
#define __TEXTCONTROL_H__

#include <stdint.h>
#include "UpDownControl.h"

namespace ATL {

    /*
        *	StringT is an Array (or derived, like FixedString) type that holds the string.
        *		implements ItemT GetAt(uint8_T), void SetAt(uint8_t, ItemT) and uint8_t getMaxCount().
        *
        *	CharacterIterator is an Iterator that implements the characters that can be selected when editing the TextControl.
        *		implements bool MoveNext(), bool MoveBack(), bool MoveTo(char) and char getCurrent() const.
        */
    template<typename StringT, typename CharacterIteratorT>
    class TextControl : public UpDownControl < TextControl<StringT, CharacterIteratorT> >
    {
        typedef UpDownControl<TextControl<StringT, CharacterIteratorT> > BaseT;
        friend BaseT;

    public:
        TextControl(StringT* str, CharacterIteratorT* iterator, uint8_t pos = 0)
            : BaseT(this, pos), _str(str), _iterator(iterator), _editIndex(0)
        { }

        virtual void Display(DisplayWriter* output, Control::ControlDisplayMode mode = Control::modeNormal)
        {
            BaseT::Display(output, mode);

            if (mode == Control::modeCursor && BaseT::getIsActive())
            {
                output->SetCursor(DisplayWriter::DontCare, BaseT::getPosition() + _editIndex, BaseT::getIsSelected());
            }
        }

        virtual bool OnNavigationCommand(NavigationCommands navCmd)
        {
            bool handled = false;

            switch (navCmd)
            {
            case Left:
                handled = TryMoveCursorLeft();
                break;
            case Right:
                handled = TryMoveCursorRight();
                break;
            default:
                break;
            }

            if (handled) return true;

            return BaseT::OnNavigationCommand(navCmd);
        }

        inline bool TryMoveCursorRight()
        {
            if (BaseT::getIsSelected())
            {
                if (_editIndex + 1 < _str->getMaxCount())
                {
                    _editIndex++;
                    RepositionIterator();
                }
                return true;
            }

            return false;
        }

        inline bool TryMoveCursorLeft()
        {
            if (BaseT::getIsSelected())
            {
                if (_editIndex > 0)
                {
                    _editIndex--;
                    RepositionIterator();
                }
                return true;
            }

            return false;
        }

    protected:
        inline const char* ToString() const
        {
            return (const char*)_str;
        }

        inline void IncrementValue()
        {
            _iterator->MoveNext();
            _str->SetAt(_editIndex, _iterator->getCurrent());
        }

        inline void DecrementValue()
        {
            _iterator->MoveBack();
            _str->SetAt(_editIndex, _iterator->getCurrent());
        }

        inline void RepositionIterator()
        {
            _iterator->MoveTo(_str->GetAt(_editIndex));
        }

        virtual bool BeforeChangeState(Control::ControlState newState)
        {
            if (!BaseT::BeforeChangeState(newState)) return false;

            if (newState == Control::stateFocused)
            {
                _editIndex = 0;
            }

            if (newState == Control::stateSelected)
            {
                _editIndex = 0;
                RepositionIterator();
            }

            return true;
        }

    private:
        StringT* _str;
        CharacterIteratorT* _iterator;
        uint8_t _editIndex;
    };

} // ATL

#endif //__TEXTCONTROL_H__