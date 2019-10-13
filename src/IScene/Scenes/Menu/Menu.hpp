/*
** EPITECH PROJECT, 2019
** Menu.hpp
** File description:
** Menu class definition
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <irrlicht.h>

#include "IScene.hpp"
#include "ButtonID.hpp"
#include "AppContext.hpp"
#include "MusicManager.hpp"
#include "SaveGame.hpp"

using namespace irr;

class Menu : public IScene
{
private:
    bool _drawn = false;
    scene::ISceneNode *_node = nullptr;

    video::ITexture *_back = nullptr;
    gui::IGUIImage *_guiBack = nullptr;

    gui::IGUIButton *_play = nullptr;
    video::ITexture *_play_button = nullptr;
    video::ITexture *_play_button_pressed = nullptr;

    gui::IGUIButton *_settings = nullptr;
    video::ITexture *_settings_button = nullptr;
    video::ITexture *_settings_button_pressed = nullptr;

    gui::IGUIButton *_quit = nullptr;
    video::ITexture *_quit_button = nullptr;
    video::ITexture *_quit_button_pressed = nullptr;

    gui::IGUIButton *_load = nullptr;
    video::ITexture *_load_button = nullptr;
    video::ITexture *_load_button_pressed = nullptr;

    AppContext *_context;
    //MusicManager _musicManager;
    SaveGame *_save;

    void setButtonNorm(gui::IGUIButton *);
public:
    Menu(AppContext *);
    ~Menu() final;

    void draw() final;
    void destroy() final;
    void event(EventReceiver &, ITimer *, SceneID &) final;
};

#endif
