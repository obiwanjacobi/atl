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

#ifndef __TEXTCONTROL_H__
#define __TEXTCONTROL_H__

#include <stdint.h>
#include "UpDownControl.h"

namespace ATL {

    /** The TextControl is a text edit control that allows a FixedString to be edited.
     *	\tparam StringT is an Array (or derived, like FixedString) type that holds the string and implements 
     *  `typedef ItemT`
     *  `ItemT GetAt(uint8_T)` (Array)
     *  `void SetAt(uint8_t, ItemT)` (FixedArray)
     *  `uint8_t getCapacity()` (Array).
     *	\tparam CharacterIterator is an Iterator that manages the characters that can be selected 
     *  when editing the TextControl and implements:
     *  `bool MoveNext()` (Iterator)
     *  `bool MoveBack()` (Iterator)
     *  `bool MoveTo(char)` (Iterator)
     *  `char getCurrent() const` (Iterator).
     */
    template<typename StringT, typename CharacterIteratorT>
    class TextControl : public UpDownControl<TextControl<StringT, CharacterIteratorT> >
    {
        typedef UpDownControl<TextControl<StringT, CharacterIteratorT> > BaseT;
        friend BaseT;

    public:
        /** Constructs an initialized instance.
         *  \param str points to the string buffer of the FixedString that is being edited.
         *  \param iterator points to the Iterator that provides the characters during editing.
         *  \param pos is an optional position relative to its siblings.
         */
        TextControl(StringT* str, CharacterIteratorT* iterator, uint8_t pos = 0)
            : BaseT(this, pos), _str(str), _iterator(iterator), _editIndex(0)
        { }

        /** Overridden to display the cursor on the character position that is being edited.
         *  \param output is used to output text and position the cursor.
         *  \mode indicates what to display.
         */
        virtual void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal)
        {
            BaseT::Display(output, mode);

            if (mode == ControlDisplayMode::Cursor && BaseT::getIsActive())
            {
                output->SetCursor(DisplayWriter::DontCare, BaseT::getPosition() + _editIndex, BaseT::getIsSelected());
            }
        }

        /** Handles the `Left` and `Right` navigation commands to change editing position inside the string.
         *  \param navCmd is the navigation command.
         *  \return Returns true if the command was handled.
         */
        virtual bool OnNavigationCommand(NavigationCommands navCmd)
        {
            bool handled = false;

            switch (navCmd)
            {
            case NavigationCommands::Left:
                handled = TryMoveCursorLeft();
                break;
            case NavigationCommands::Right:
                handled = TryMoveCursorRight();
                break;
            default:
                break;
            }

            if (handled) return true;

            return BaseT::OnNavigationCommand(navCmd);
        }

        /** Attempts to move the editing cursor to the right.
         *  \return Returns true when successful (even when the end of the string was reached).
         */
        inline bool TryMoveCursorRight()
        {
            if (BaseT::getIsSelected())
            {
                if (_editIndex + 1 < _str->getCapacity())
                {
                    _editIndex++;
                    RepositionIterator();
                }
                return true;
            }

            return false;
        }

        /** Attempts to move the editing cursor to the left.
         *  \return Returns true when successful (even when the start of the string was reached).
         */
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
        /** Called by the UpDownControl to retrieve the 'value' to display.
         *  \return Returns the pointer to the string.
         */
        inline const char* ToString() const
        {
            return (const char*)_str;
        }

        /** Called by the UpDownControl to increment the 'value' - char at edit position.
         */
        inline void IncrementValue()
        {
            _iterator->MoveNext();
            _str->SetAt(_editIndex, _iterator->getCurrent());
        }

        /** Called by the UpDownControl to decrement the 'value' - char at edit position.
         */
        inline void DecrementValue()
        {
            _iterator->MoveBack();
            _str->SetAt(_editIndex, _iterator->getCurrent());
        }

        /** Helper method that sets the CharacterIteratorT at the character at the current edit position.
         */
        inline void RepositionIterator()
        {
            _iterator->MoveTo(_str->GetAt(_editIndex));
        }

        /** Overridden to manage the character edit position when going in/out of `stateFocused` and `stateSelected`.
         *  Does not alter behavior.
         *  \param newState is the proposed state.
         *  \return Returns true when the state change is allowed.
         */
        virtual bool BeforeChangeState(ControlState newState)
        {
            if (!BaseT::BeforeChangeState(newState)) return false;

            if (newState == ControlState::Focused)
            {
                _editIndex = 0;
            }

            if (newState == ControlState::Selected)
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