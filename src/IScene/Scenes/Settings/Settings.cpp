/*
** EPITECH PROJECT, 2019
** Settings.cpp
** File description:
** Settings class implementation
*/

#include "Settings.hpp"

Settings::Settings(AppContext *context)
{
    _context = context;
    _node = _context->scenemgr->addEmptySceneNode();

    _back = _context->vidriver->getTexture("./assets/back1.png");
    _name_tag = _context->vidriver->getTexture("./assets/name.png");
    _settings = _context->vidriver->getTexture("./assets/settings.png");

    _arrow_up = _context->vidriver->getTexture("./assets/selection/up.png");
    _arrow_up_pressed = _context->vidriver->getTexture("./assets/selection/upp.png");
    _arrow_down = _context->vidriver->getTexture("./assets/selection/down.png");
    _arrow_down_pressed = _context->vidriver->getTexture("./assets/selection/downp.png");

    _music_tag = _context->vidriver->getTexture("./assets/Settings/music.png");
    _effect_tag = _context->vidriver->getTexture("./assets/Settings/sound_eff.png");
    _up_tag = _context->vidriver->getTexture("./assets/Settings/up.png");
    _down_tag = _context->vidriver->getTexture("./assets/Settings/down.png");
    _left_tag = _context->vidriver->getTexture("./assets/Settings/left.png");
    _right_tag = _context->vidriver->getTexture("./assets/Settings/right.png");
    _action_tag = _context->vidriver->getTexture("./assets/Settings/action.png");

    _player.push_back(_context->vidriver->getTexture("./assets/selection/p1.png"));
    _player.push_back(_context->vidriver->getTexture("./assets/selection/p2.png"));
    _player.push_back(_context->vidriver->getTexture("./assets/selection/p3.png"));
    _player.push_back(_context->vidriver->getTexture("./assets/selection/p4.png"));
    _player_select = _player[0];
    _musicT.push_back(_context->vidriver->getTexture("./assets/music.png"));
    _musicT.push_back(_context->vidriver->getTexture("./assets/music_cut.png"));
    _effectT.push_back(_context->vidriver->getTexture("./assets/effects.png"));
    _effectT.push_back(_context->vidriver->getTexture("./assets/effects_cut.png"));
    _music_set = _musicT[0];
    _effect_set = _effectT[0];
    choose = 0;
    _init_name();
}

Settings::~Settings()
{
}

void Settings::draw()
{
    _context->guienv->addImage(_back, core::position2d<int>(0,0));
    _settingsI = _context->guienv->addImage(core::rect<s32>(370, 80, 770, 180));
    _settingsI->setImage(_settings);
    _settingsI->setScaleImage(true);
    _music = _context->guienv->addButton(core::rect<s32>(120, 800, 320, 1000), 0, MUSIC);
    _effects = _context->guienv->addButton(core::rect<s32>(490, 850, 640, 1000), 0, EFFECT);
    if (_context->music == true) {
        _music_set = _musicT[0];
    } else {
        _music_set = _musicT[1];
    }
    if (_context->sound_effect == true) {
        _effect_set = _effectT[0];
    } else {
        _effect_set = _effectT[1];
    }
    _music->setImage((_music_set));
    _effects->setImage((_effect_set));
    draw_player();
    draw_tags();
    draw_keybind();
    setButton(_music);
    setButton(_effects);
}

void Settings::draw_keybind() {
    _upbind = _context->guienv->addButton(core::rect<s32>(1400, 400, 1600, 475), 0, UP_BIND);
    _upbind->setText(core::stringw(_key_name[_player_binding._up].c_str()).c_str());

    _downbind = _context->guienv->addButton(core::rect<s32>(1400, 525, 1600, 600), 0, DOWN_BIND);
    _downbind->setText(core::stringw(_key_name[_player_binding._down].c_str()).c_str());

    _leftbind = _context->guienv->addButton(core::rect<s32>(1400, 650, 1600, 725), 0, LEFT_BIND);
    _leftbind->setText(core::stringw(_key_name[_player_binding._left].c_str()).c_str());

    _rightbind = _context->guienv->addButton(core::rect<s32>(1400, 775, 1600, 850), 0, RIGHT_BIND);
    _rightbind->setText(core::stringw(_key_name[_player_binding._right].c_str()).c_str());

    _actionbind = _context->guienv->addButton(core::rect<s32>(1400, 900, 1600, 975), 0, ACTION_BIND);
    _actionbind->setText(core::stringw(_key_name[_player_binding._action].c_str()).c_str());
}

void Settings::setButton(gui::IGUIButton *button)
{
    button->setScaleImage(true);
    button->setUseAlphaChannel(true);
    button->setDrawBorder(false);
}

void Settings::draw_player()
{
    _up = _context->guienv->addButton(core::rect<s32>(1450, 50, 1550, 100), 0, UP_CLICK);
    _down = _context->guienv->addButton(core::rect<s32>(1450, 250, 1550, 300), 0, DOWN_CLICK);
    _up->setImage(_arrow_up);
    _down->setImage(_arrow_down);
    _up->setPressedImage(_arrow_up_pressed);
    _down->setPressedImage(_arrow_down_pressed);
    setButton(_up);
    setButton(_down);
    if (choose == 0) {
        _player_select = _player[0];
        _player_binding = _context->player1;
    } else if (choose == 1) {
        _player_select = _player[1];
        _player_binding = _context->player2;
    } else if (choose == 2) {
        _player_select = _player[2];
        _player_binding = _context->player3;
    } else {
        _player_select = _player[3];
        _player_binding = _context->player4;
    }
    _context->guienv->addImage(_player_select, core::position2d<int>(1320,120));
}

void Settings::draw_tags()
{
    _musicI = _context->guienv->addImage(core::rect<s32>(80, 650, 380, 750));
    _musicI->setImage(_music_tag);
    _musicI->setScaleImage(true);
    _effectI = _context->guienv->addImage(core::rect<s32>(400, 650, 780, 750));
    _effectI->setImage(_effect_tag);
    _effectI->setScaleImage(true);
    _upI = _context->guienv->addImage(core::rect<s32>(1000, 400, 1200, 475));
    _upI->setImage(_up_tag);
    _upI->setScaleImage(true);
    _downI = _context->guienv->addImage(core::rect<s32>(1000, 525, 1200, 600));
    _downI->setImage(_down_tag);
    _downI->setScaleImage(true);
    _leftI = _context->guienv->addImage(core::rect<s32>(1000, 650, 1200, 725));
    _leftI->setImage(_left_tag);
    _leftI->setScaleImage(true);
    _rightI = _context->guienv->addImage(core::rect<s32>(1000, 775, 1200, 850));
    _rightI->setImage(_right_tag);
    _rightI->setScaleImage(true);
    _actionI = _context->guienv->addImage(core::rect<s32>(1000, 900, 1200, 975));
    _actionI->setImage(_action_tag);
    _actionI->setScaleImage(true);
}


void Settings::destroy()
{
    _node->removeAll();
    _context->guienv->clear();
}

void Settings::event(EventReceiver &receiver, ITimer *timer, SceneID &shown)
{
    if (receiver.isKeyDown(irr::KEY_ESCAPE)) {
        shown = MENU_SCENE;
    }
    if (choose == 0) {
        _context->player1 = binding(receiver, _context->player1);
    } else if (choose == 1) {
        _context->player2 = binding(receiver, _context->player2);
    } else if (choose == 2) {
        _context->player3 = binding(receiver, _context->player3);
    } else {
        _context->player4 = binding(receiver, _context->player4);
    }
    music_effect_check(receiver, timer, shown);
    change_player(receiver, timer, shown);

}

PlayerBind Settings::binding(EventReceiver &receiver, PlayerBind &player)
{
    EKEY_CODE check = receiver.getLastKey();

    check = receiver.getLastKey();
    if (_upbind->isPressed()) {
        check = receiver.getLastKey();
        player._up = check_key(receiver, check);
        _clear_display();
    } else if (_downbind->isPressed()) {
        check = receiver.getLastKey();
        player._down = check_key(receiver, check);
        _clear_display();
    } else if (_leftbind->isPressed()) {
        check = receiver.getLastKey();
        player._left = check_key(receiver, check);
        _clear_display();
    } else if (_rightbind->isPressed()) {
        check = receiver.getLastKey();
        player._right = check_key(receiver, check);
        _clear_display();
    } else if (_actionbind->isPressed()) {
        check = receiver.getLastKey();
        player._action = check_key(receiver, check);
        _clear_display();
    } else {
        //nothing to do
    }
    return (player);
}

EKEY_CODE Settings::check_key(EventReceiver &receiver, EKEY_CODE check)
{
    switch (check)
    {
    case 8:
        return (KEY_BACK);
        break;
    case 9:
        return (KEY_TAB);
        break;
    case 13:
        return (KEY_RETURN);
        break;
    case 16:
        return (KEY_SHIFT);
        break;
    case 17:
        return (KEY_CONTROL);
        break;
    case 18:
        return (KEY_MENU);
        break;
    case 20:
        return (KEY_CAPITAL);
        break;
    case 32:
        return (KEY_SPACE);
        break;
    case 33:
        return (KEY_PRIOR);
        break;
    case 34:
        return (KEY_NEXT);
        break;
    case 37:
        return (KEY_LEFT);
        break;
    case 38:
        return (KEY_UP);
        break;
    case 39:
        return (KEY_RIGHT);
        break;
    case 40:
        return (KEY_DOWN);
        break;
    case 45:
        return (KEY_INSERT);
        break;
    case 46:
        return (KEY_DELETE);
        break;
    case 48:
        return (KEY_KEY_0);
        break;
    case 49:
        return (KEY_KEY_1);
        break;
    case 50:
        return (KEY_KEY_2);
        break;
    case 51:
        return (KEY_KEY_3);
        break;
    case 52:
        return (KEY_KEY_4);
        break;
    case 53:
        return (KEY_KEY_5);
        break;
    case 54:
        return (KEY_KEY_6);
        break;
    case 55:
        return (KEY_KEY_7);
        break;
    case 56:
        return (KEY_KEY_8);
        break;
    case 57:
        return (KEY_KEY_9);
        break;
    case 65:
        return (KEY_KEY_A);
        break;
    case 66:
        return (KEY_KEY_B);
        break;
    case 67:
        return (KEY_KEY_C);
        break;
    case 68:
        return (KEY_KEY_D);
        break;
    case 69:
        return (KEY_KEY_E);
        break;
    case 70:
        return (KEY_KEY_F);
        break;
    case 71:
        return (KEY_KEY_G);
        break;
    case 72:
        return (KEY_KEY_H);
        break;
    case 73:
        return (KEY_KEY_I);
        break;
    case 74:
        return (KEY_KEY_J);
        break;
    case 75:
        return (KEY_KEY_K);
        break;
    case 76:
        return (KEY_KEY_L);
        break;
    case 77:
        return (KEY_KEY_M);
        break;
    case 78:
        return (KEY_KEY_N);
        break;
    case 79:
        return (KEY_KEY_O);
        break;
    case 80:
        return (KEY_KEY_P);
        break;
    case 81:
        return (KEY_KEY_Q);
        break;
    case 82:
        return (KEY_KEY_R);
        break;
    case 83:
        return (KEY_KEY_S);
        break;
    case 84:
        return (KEY_KEY_T);
        break;
    case 85:
        return (KEY_KEY_U);
        break;
    case 86:
        return (KEY_KEY_V);
        break;
    case 87:
        return (KEY_KEY_W);
        break;
    case 88:
        return (KEY_KEY_X);
        break;
    case 89:
        return (KEY_KEY_Y);
        break;
    case 90:
        return (KEY_KEY_Z);
        break;
    case 163:
        return (KEY_RCONTROL);
        break;
    default:
        break;
    }
    return(KEY_KEY_0);
}

void Settings::music_effect_check(EventReceiver &receiver, ITimer *timer, SceneID &shown)
{
    if (_music->isPressed() && _context->music == true) {
        _music_set = _musicT[1];
        _context->music = false;
        _clear_display();
    } else if (_music->isPressed() && _context->music == false) {
        _music_set = _musicT[0];
        _context->music = true;
        _clear_display();
    } else {
        //nothing to do
    }
    if (_effects->isPressed() && _context->sound_effect == true) {
        _effect_set = _effectT[1];
        _context->sound_effect = false;
        _clear_display();
    } else if (_effects->isPressed() && _context->sound_effect == false) {
        _effect_set = _effectT[0];
        _context->sound_effect = true;
        _clear_display();
    } else {
        //nothing to do
    }
}

void Settings::change_player(EventReceiver &receiver, ITimer *timer, SceneID &shown)
{
    if (_up->isPressed()) {
        choose = choose + 1;
        if (choose > 3) {
            choose = 0;
        } else {
            //nothing to do
        }
        _clear_display();
    } else if (_down->isPressed()) {
        choose = choose - 1;
        if (choose < 0) {
            choose = 3;
        } else {
            //nothing to do
        }
        _clear_display();
    } else {
        //nothing to do
    }
}

void Settings::_clear_display()
{
    _context->guienv->clear();
    draw();
}


void Settings::_init_name()
{
    _key_name.push_back(""); // 0
    _key_name.push_back(""); // 1
    _key_name.push_back(""); // 2
    _key_name.push_back(""); // 3
    _key_name.push_back(""); // 4
    _key_name.push_back(""); // 5
    _key_name.push_back(""); // 6
    _key_name.push_back(""); // 7
    _key_name.push_back("BACKSPACE"); // 8
    _key_name.push_back("TAB"); // 9
    _key_name.push_back(""); // 10
    _key_name.push_back(""); // 11
    _key_name.push_back(""); // 12
    _key_name.push_back("ENTER"); // 13
    _key_name.push_back(""); // 14
    _key_name.push_back(""); // 15
    _key_name.push_back("SHIFT"); // 16
    _key_name.push_back("CTRL"); // 17
    _key_name.push_back("ALT"); // 18
    _key_name.push_back(""); // 19
    _key_name.push_back("CAPSLOCK"); // 20
    _key_name.push_back(""); // 21
    _key_name.push_back(""); // 22
    _key_name.push_back(""); // 23
    _key_name.push_back(""); // 24
    _key_name.push_back(""); // 25
    _key_name.push_back(""); // 26
    _key_name.push_back(""); // 27
    _key_name.push_back(""); // 28
    _key_name.push_back(""); // 29
    _key_name.push_back(""); // 30
    _key_name.push_back(""); // 31
    _key_name.push_back("SPACEBAR"); // 32
    _key_name.push_back("PAGE UP"); // 33
    _key_name.push_back("PAGE DOWN"); // 34
    _key_name.push_back(""); // 35
    _key_name.push_back(""); // 36
    _key_name.push_back("LEFT ARROW"); // 37
    _key_name.push_back("UP ARROW"); // 38
    _key_name.push_back("RIGHT ARROW"); // 39
    _key_name.push_back("DOWN ARROW"); // 40
    _key_name.push_back(""); // 41
    _key_name.push_back(""); // 42
    _key_name.push_back(""); // 43
    _key_name.push_back(""); // 44
    _key_name.push_back("INSERT"); // 45
    _key_name.push_back("SUPPR"); // 46
    _key_name.push_back(""); // 47
    _key_name.push_back("0"); // 48
    _key_name.push_back("1"); // 49
    _key_name.push_back("2"); // 50
    _key_name.push_back("3"); // 51
    _key_name.push_back("4"); // 52
    _key_name.push_back("5"); // 53
    _key_name.push_back("6"); // 54
    _key_name.push_back("7"); // 55
    _key_name.push_back("8"); // 56
    _key_name.push_back("9"); // 57
    _key_name.push_back(""); // 58
    _key_name.push_back(""); // 59
    _key_name.push_back(""); // 60
    _key_name.push_back(""); // 61
    _key_name.push_back(""); // 62
    _key_name.push_back(""); // 63
    _key_name.push_back(""); // 64
    _key_name.push_back("A"); // 65
    _key_name.push_back("B"); // 66
    _key_name.push_back("C"); // 67
    _key_name.push_back("D"); // 68
    _key_name.push_back("E"); // 69
    _key_name.push_back("F"); // 70
    _key_name.push_back("G"); // 71
    _key_name.push_back("H"); // 72
    _key_name.push_back("I"); // 73
    _key_name.push_back("J"); // 74
    _key_name.push_back("K"); // 75
    _key_name.push_back("L"); // 76
    _key_name.push_back("M"); // 77
    _key_name.push_back("N"); // 78
    _key_name.push_back("O"); // 79
    _key_name.push_back("P"); // 80
    _key_name.push_back("Q"); // 81
    _key_name.push_back("R"); // 82
    _key_name.push_back("S"); // 83
    _key_name.push_back("T"); // 84
    _key_name.push_back("U"); // 85
    _key_name.push_back("V"); // 86
    _key_name.push_back("W"); // 87
    _key_name.push_back("X"); // 88
    _key_name.push_back("Y"); // 89
    _key_name.push_back("Z"); // 90
    _key_name.push_back(""); // 91
    _key_name.push_back(""); // 92
    _key_name.push_back(""); // 93
    _key_name.push_back(""); // 94
    _key_name.push_back(""); // 95
    _key_name.push_back(""); // 96
    _key_name.push_back(""); // 97
    _key_name.push_back(""); // 98
    _key_name.push_back(""); // 99
    _key_name.push_back(""); // 100
    _key_name.push_back(""); // 101
    _key_name.push_back(""); // 102
    _key_name.push_back(""); // 103
    _key_name.push_back(""); // 104
    _key_name.push_back(""); // 105
    _key_name.push_back(""); // 106
    _key_name.push_back(""); // 107
    _key_name.push_back(""); // 108
    _key_name.push_back(""); // 109
    _key_name.push_back(""); // 110
    _key_name.push_back(""); // 111
    _key_name.push_back(""); // 112
    _key_name.push_back(""); // 113
    _key_name.push_back(""); // 114
    _key_name.push_back(""); // 115
    _key_name.push_back(""); // 116
    _key_name.push_back(""); // 117
    _key_name.push_back(""); // 118
    _key_name.push_back(""); // 119
    _key_name.push_back(""); // 120
    _key_name.push_back(""); // 121
    _key_name.push_back(""); // 122
    _key_name.push_back(""); // 123
    _key_name.push_back(""); // 124
    _key_name.push_back(""); // 125
    _key_name.push_back(""); // 126
    _key_name.push_back(""); // 127
    _key_name.push_back(""); // 128
    _key_name.push_back(""); // 129
    _key_name.push_back(""); // 130
    _key_name.push_back(""); // 131
    _key_name.push_back(""); // 132
    _key_name.push_back(""); // 133
    _key_name.push_back(""); // 134
    _key_name.push_back(""); // 135
    _key_name.push_back(""); // 136
    _key_name.push_back(""); // 137
    _key_name.push_back(""); // 138
    _key_name.push_back(""); // 139
    _key_name.push_back(""); // 140
    _key_name.push_back(""); // 141
    _key_name.push_back(""); // 142
    _key_name.push_back(""); // 143
    _key_name.push_back(""); // 144
    _key_name.push_back(""); // 145
    _key_name.push_back(""); // 146
    _key_name.push_back(""); // 147
    _key_name.push_back(""); // 148
    _key_name.push_back(""); // 149
    _key_name.push_back(""); // 150
    _key_name.push_back(""); // 151
    _key_name.push_back(""); // 152
    _key_name.push_back(""); // 153
    _key_name.push_back(""); // 154
    _key_name.push_back(""); // 155
    _key_name.push_back(""); // 156
    _key_name.push_back(""); // 157
    _key_name.push_back(""); // 158
    _key_name.push_back(""); // 159
    _key_name.push_back("LEFT SHIFT"); // 160
    _key_name.push_back("RIGHT SHIFT"); // 161
    _key_name.push_back("LEFT CTRL"); // 162
    _key_name.push_back("RIGHT CTRL"); // 163
    _key_name.push_back(""); // 164
    _key_name.push_back(""); // 165
    _key_name.push_back(""); // 166
    _key_name.push_back(""); // 167
    _key_name.push_back(""); // 168
    _key_name.push_back(""); // 169
    _key_name.push_back(""); // 170
}