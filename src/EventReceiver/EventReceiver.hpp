/*
** EPITECH PROJECT, 2019
** EventReceiver.hpp
** File description:
** EventReceiver class definition
*/

#ifndef EVENTRECEIVER_HPP_
#define EVENTRECEIVER_HPP_

#include <fstream>
#include <iostream>
#include <irrlicht.h>
#include <map>

#include "ButtonID.hpp"

using namespace irr;
using namespace gui;

class EventReceiver : public IEventReceiver
{
private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    EKEY_CODE _last = KEY_KEY_CODES_COUNT;
    gui::ICursorControl *_cursor = nullptr;
    bool _mouseLeft = false;
    bool _mouseRight = false;
    /* Load Game */
    std::string _load_path;
    bool _can_load = false;
public:
    EventReceiver();
    ~EventReceiver() = default;

    bool isKeyDown(EKEY_CODE keyCode) const;
    void setCursorControl(gui::ICursorControl *);
    EKEY_CODE getLastKey() const;
    core::position2d<s32> getCursorPos();
    bool isMouseLeftPressed();
    bool isMouseRightPressed();

    bool OnEvent(const SEvent &) final;
    /* SaveGame */
    bool loadFile(const SEvent &);
    bool isLoadable();
    std::string getLoadPath();
};

#endif
