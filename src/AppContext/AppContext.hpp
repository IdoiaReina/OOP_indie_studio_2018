/*
** EPITECH PROJECT, 2019
** AppContext.hpp
** File description:
** Context of App
*/

#ifndef APPCONTEXT_HPP_
#define APPCONTEXT_HPP_

#include <irrlicht.h>
#include <utility>

#include "IMap.hpp"

using namespace irr;

enum PlayerState
{
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    PLAYER_3 = 2,
    PLAYER_4 = 3,
    BOT = 4,
    DISABLED = 5
};

enum PlayerColor
{
    GREEN = 0,
    RED = 1,
    PURPLE = 2,
    BLUE = 3
};

struct PlayerBind
{
    EKEY_CODE _up;
    EKEY_CODE _down;
    EKEY_CODE _left;
    EKEY_CODE _right;
    EKEY_CODE _action;
};

struct AppContext
{
    video::IVideoDriver *vidriver = nullptr;
    scene::ISceneManager *scenemgr = nullptr;
    gui::IGUIEnvironment *guienv = nullptr;
    MapID map = NOT_SELECTED;
    PlayerState player_green = PLAYER_1;
    PlayerState player_red = BOT;
    PlayerState player_purple = BOT;
    PlayerState player_blue = BOT;
    PlayerState winner = PLAYER_1;
    // add Settings param
    bool music;
    bool sound_effect;
    PlayerBind player1;
    PlayerBind player2;
    PlayerBind player3;
    PlayerBind player4;
};

#endif
