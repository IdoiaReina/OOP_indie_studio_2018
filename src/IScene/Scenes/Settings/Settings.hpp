/*
** EPITECH PROJECT, 2019
** Settings.hpp
** File description:
** Settings class definition
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <irrlicht.h>
#include <stdio.h>
#include <iostream>

#include "IScene.hpp"
#include "AppContext.hpp"
#include "RandomMap.hpp"

using namespace irr;

enum SettingID {
    MUSIC = 0,
    EFFECT = 1,
    ALL_SOUND = 2,
    UP_CLICK = 3,
    DOWN_CLICK = 4,
    UP_BIND = 5,
    DOWN_BIND = 6,
    LEFT_BIND = 7,
    RIGHT_BIND = 8,
    ACTION_BIND = 9
};

class Settings : public IScene
{
private:

    scene::ISceneNode *_node = nullptr;
    AppContext *_context;

    //Texture(s) :
    video::ITexture *_back = nullptr;
    video::ITexture *_name_tag = nullptr;
    video::ITexture *_settings = nullptr;
    video::ITexture *_arrow_up = nullptr;
    video::ITexture *_arrow_down = nullptr;
    video::ITexture *_arrow_up_pressed = nullptr;
    video::ITexture *_arrow_down_pressed = nullptr;
    video::ITexture *_player_select = nullptr;
    video::ITexture *_music_set = nullptr;
    video::ITexture *_effect_set = nullptr;

    //Tag(s)
    video::ITexture *_music_tag = nullptr;
    video::ITexture *_effect_tag = nullptr;
    video::ITexture *_up_tag = nullptr;
    video::ITexture *_down_tag = nullptr;
    video::ITexture *_left_tag = nullptr;
    video::ITexture *_right_tag = nullptr;
    video::ITexture *_action_tag = nullptr;

    //Image(s) :
    gui::IGUIImage *_signI = nullptr;
    gui::IGUIImage *_settingsI = nullptr;
    gui::IGUIImage *_musicI = nullptr;
    gui::IGUIImage *_effectI = nullptr;
    gui::IGUIImage *_upI = nullptr;
    gui::IGUIImage *_downI = nullptr;
    gui::IGUIImage *_leftI = nullptr;
    gui::IGUIImage *_rightI = nullptr;
    gui::IGUIImage *_actionI = nullptr;

    //Text
    gui::IGUIStaticText *_upText = nullptr;
    gui::IGUIStaticText *_downText = nullptr;
    gui::IGUIStaticText *_leftText = nullptr;
    gui::IGUIStaticText *_rightText = nullptr;
    gui::IGUIStaticText *_actionText = nullptr;

    //Button(s) :
    gui::IGUIButton *_music = nullptr;
    gui::IGUIButton *_effects = nullptr;
    gui::IGUIButton *_up = nullptr;
    gui::IGUIButton *_down = nullptr;
    gui::IGUIButton *_upbind = nullptr;
    gui::IGUIButton *_downbind = nullptr;
    gui::IGUIButton *_leftbind = nullptr;
    gui::IGUIButton *_rightbind = nullptr;
    gui::IGUIButton *_actionbind = nullptr;

    //Variable(s) :
    int choose;
    std::vector<video::ITexture *> _player;
    std::vector<video::ITexture *> _musicT;
    std::vector<video::ITexture *> _effectT;
    std::vector<std::string> _key_name;
    PlayerBind _player_binding;

    //Function(s) :
    void draw_player(void);
    void draw_tags(void);
    void draw_keybind(void);
    void setButton(gui::IGUIButton *);
    void _clear_display();
    void _init_name();

    //Event Method(s) :
    void change_player(EventReceiver &, ITimer *, SceneID &);
    void music_effect_check(EventReceiver &, ITimer *, SceneID &);
    PlayerBind binding(EventReceiver &, PlayerBind &);
    EKEY_CODE check_key(EventReceiver &, EKEY_CODE);

public:
    Settings(AppContext *);
    ~Settings() final;

    void draw() final;
    void destroy() final;
    void event(EventReceiver &, ITimer *, SceneID &) final;
};

#endif
