/*
** EPITECH PROJECT, 2019
** EventReceiver.cpp
** File description:
** EventReceiver class implementation
*/

#include "EventReceiver.hpp"

EventReceiver::EventReceiver()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

bool EventReceiver::OnEvent(const SEvent &event)
{
    loadFile(event);

    switch (event.EventType) {
    case irr::EET_KEY_INPUT_EVENT:
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	_last = event.KeyInput.Key;
	break;
    case irr::EET_MOUSE_INPUT_EVENT:
        _mouseLeft = event.MouseInput.isLeftPressed();
        _mouseRight = event.MouseInput.isRightPressed();
	break;
    case irr::EET_LOG_TEXT_EVENT:
	return true;
    default:
	break;
    }
    return false;
}

void EventReceiver::setCursorControl(gui::ICursorControl *cursor)
{
    _cursor = cursor;
}

EKEY_CODE EventReceiver::getLastKey() const
{
    return _last;
}

core::position2d<s32> EventReceiver::getCursorPos()
{
    return _cursor->getPosition();
}

bool EventReceiver::isMouseLeftPressed()
{
    return _mouseLeft;
}

bool EventReceiver::isMouseRightPressed()
{
    return _mouseRight;
}

bool EventReceiver::isKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool EventReceiver::loadFile(const SEvent &event)
{
    if (event.EventType == EET_GUI_EVENT) {
        s32 id = event.GUIEvent.Caller->getID();
        if (event.GUIEvent.EventType == EGET_FILE_SELECTED) {
            IGUIFileOpenDialog* dia =(IGUIFileOpenDialog*)event.GUIEvent.Caller;
            std::wstring ws(dia->getFileName());
            std::string str(ws.begin(), ws.end());
            if (str[str.length() -1] != 's' || str[str.length() - 2] != 'i')
                return false;
            else {
                _can_load = true;
                _load_path = str;
            }
        }
    }
    return true;
}

bool EventReceiver::isLoadable()
{
    return (_can_load);
}

std::string EventReceiver::getLoadPath()
{
    return (_load_path);
}