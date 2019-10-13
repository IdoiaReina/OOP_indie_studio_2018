/*
** EPITECH PROJECT, 2019
** Indie.hpp
** File description:
** Indie class definition
*/

#ifndef INDIE_HPP_
#define INDIE_HPP_

#include <iostream>
#include <irrlicht.h>

#include "GameException.hpp"
#include "SceneStock.hpp"
#include "EventReceiver.hpp"
#include "ButtonID.hpp"
#include "IScene.hpp"
#include "AppContext.hpp"

using namespace irr;

class Indie
{
private:
    IrrlichtDevice *_device = nullptr;

    ITimer *_timer = nullptr;
    gui::ICursorControl *_cursor = nullptr;

    AppContext _context;

    SceneStock _scenes;
    EventReceiver _receiver;
    SceneID _shown = SPLASH_SCENE;

    void event();
public:
    Indie();
    ~Indie();

    void letsgo();
};

#endif
