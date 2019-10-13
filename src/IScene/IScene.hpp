/*
** EPITECH PROJECT, 2019
** IScene.hpp
** File description:
** IScene interface
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include <irrlicht.h>

#include "EventReceiver.hpp"

using namespace irr;

enum SceneID {
    CLOSE_SCENE = -1,
    SPLASH_SCENE = 0,
    MENU_SCENE = 1,
    SETTINGS_SCENE,
    CHOOSEPLAYER_SCENE,
    MAPSELECTOR_SCENE,
    GAME_SCENE,
    END_GAME
};

class IScene
{
public:
    virtual ~IScene() = default;

    virtual void draw() = 0;
    virtual void destroy() = 0;
    virtual void event(EventReceiver &, ITimer *, SceneID &) = 0;
};

#endif
