/*
** EPITECH PROJECT, 2018
** ChoosePlayer.cpp
** File description:
** ChoosePlayer class implementation
*/

#include <iostream>
#include "ChoosePlayer.hpp"

ChoosePlayer::ChoosePlayer(AppContext *context)
{
    _context = context;
    _node = _context->scenemgr->addEmptySceneNode();
    _back = _context->vidriver->getTexture("./assets/selection/bg.png");
    _arrow_up = _context->vidriver->getTexture("./assets/selection/up.png");
    _arrow_up_pressed = _context->vidriver->getTexture("./assets/selection/upp.png");
    _arrow_down = _context->vidriver->getTexture("./assets/selection/down.png");
    _arrow_down_pressed = _context->vidriver->getTexture("./assets/selection/downp.png");
    _file_vector();
//    _musicManager.setMusic("./assets/musics/selection_perso.ogg");
}

ChoosePlayer::~ChoosePlayer()
{
}

void ChoosePlayer::_file_vector()
{
    _pos.push_back({100, 10});
    _pos.push_back({550, 10});
    _pos.push_back({1000, 10});
    _pos.push_back({1450, 10});
    _choice.push_back(_context->player_green);
    _choice.push_back(_context->player_red);
    _choice.push_back(_context->player_purple);
    _choice.push_back(_context->player_blue);
    _status.push_back(_context->vidriver->getTexture("./assets/selection/p1.png"));
    _status.push_back(_context->vidriver->getTexture("./assets/selection/p2.png"));
    _status.push_back(_context->vidriver->getTexture("./assets/selection/p3.png"));
    _status.push_back(_context->vidriver->getTexture("./assets/selection/p4.png"));
    _status.push_back(_context->vidriver->getTexture("./assets/selection/bot.png"));
    _status.push_back(_context->vidriver->getTexture("./assets/selection/off.png"));
}

void ChoosePlayer::draw()
{
//    _musicManager.playMusic();
    _choose_correct();
    _mainImage = _context->guienv->addImage(core::rect<s32>(0, 0, 1920, 1080));
    _mainImage->setImage(_back);
    _mainImage->setScaleImage(true);
    _draw_arrow();
    _draw_status();
}

void ChoosePlayer::destroy()
{
    _node->removeAll();
    _context->guienv->clear();
    _pos.clear();
    _status.clear();
//    _musicManager.stopMusic();
}
void ChoosePlayer::_choose_correct()
{
    while (pressed_up && _choice[_where] < 4 
    && _found_in(_choice[_where])) {
        _choice[_where] = (_choice[_where] + 7) % 6;
    }
    while (pressed_down && _choice[_where] < 4 
    && _found_in(_choice[_where])) {
        _choice[_where] = (_choice[_where] + 5) % 6;
    }
}

bool ChoosePlayer::_found_in(int choosen) {
    int itr = -1;
    int occurence = 0;

    while (++itr != 4) {
        if (choosen == _choice[itr])
            ++occurence;
    }
    if (occurence > 1)
        return true;
    return false;
}

void ChoosePlayer::event(EventReceiver &receiver, ITimer *timer,  SceneID &shown)
{
    bool pressed = receiver.isKeyDown(irr::KEY_ESCAPE);
    bool mouse = receiver.isMouseLeftPressed();

    if (pressed == false) {
        echap = true;
    }
    if (mouse == false) {
        _mouse = true;
    }
    _arrow_move(receiver, timer);
    _mouse_click(receiver, timer);
    if (pressed == true && echap == true) {
        _reinit();
        shown = MENU_SCENE;
    }
    if (receiver.isKeyDown(irr::KEY_RETURN) && _check_choice()) {
        _reinit();
        _context->player_green = (PlayerState)_choice[0];
        _context->player_red = (PlayerState)_choice[1];
        _context->player_purple = (PlayerState)_choice[2];
        _context->player_blue = (PlayerState)_choice[3];
        shown = MAPSELECTOR_SCENE;
    }
}

bool ChoosePlayer::_check_choice()
{
    int nbr_entity = 0;
    int iterator = -1;

    while (++iterator != 4) {
        if (_choice[iterator] != 5) {
            nbr_entity++;
        }
    }
    if (nbr_entity >= 2) {
        return true;
    }
    return false;
}

void ChoosePlayer::_arrow_move(EventReceiver &receiver, ITimer *timer)
{
    static int time = 0;
    int actual = timer->getTime();
    int arrow = 36;
    bool change_selected = false;
    bool pressed = false;

    while (++arrow != 41) {
        if (receiver.isKeyDown((EKEY_CODE)arrow) && actual - time > 200) {
            time = timer->getTime();
            if (arrow % 2 == 1)
                _where = (_where + (arrow - 38) + 4) % 4;
            else
                _choice[_where] = (_choice[_where] - (arrow - 39) + 6) % 6;
            _clear_display();
            pressed = true;
        } else if (receiver.isKeyDown((EKEY_CODE)arrow))
            pressed = true;
        _status_arrow(arrow, receiver);
    }
    keyboard_pressed = pressed;
    return;
}

void ChoosePlayer::_status_arrow(int key, EventReceiver &receiver)
{
    bool old_up = pressed_up;
    bool old_down = pressed_down;

    if (key % 2 == 1)
        return;
    if (key == 38) {
        if (receiver.isKeyDown((EKEY_CODE)key))
            pressed_up = true;
    } else if (key == 40) {
        if (receiver.isKeyDown((EKEY_CODE)key))
            pressed_down = true;
    }
    if (old_up != pressed_down || old_down != pressed_down) {
        _clear_display();
    }
}

void ChoosePlayer::_draw_arrow()
{
    video::ITexture *up = nullptr;
    video::ITexture *down = nullptr;

    if (pressed_up == true)
        up = _arrow_up_pressed;
    else
        up = _arrow_up;
    if (pressed_down == true)
        down = _arrow_down_pressed;
    else
        down = _arrow_down;
    _mainImage = _context->guienv->addImage({_pos[_where].X + 100, _pos[_where].Y + 20, 
        _pos[_where].X + 230, _pos[_where].Y + 106});
    _mainImage->setImage(up);
    _mainImage->setScaleImage(true);
    _mainImage = _context->guienv->addImage({_pos[_where].X + 100, _pos[_where].Y + 200, 
        _pos[_where].X + 230, _pos[_where].Y + 286});
    _mainImage->setImage(down);
    _mainImage->setScaleImage(true);
}

void ChoosePlayer::_draw_status()
{
    int itr = -1;

    while (++itr != 4) {
        _mainImage = _context->guienv->addImage({_pos[itr].X, _pos[itr].Y + 116, 
            _pos[itr].X + 330, _pos[itr].Y + 196});
        _mainImage->setImage(_status[_choice[itr]]);
        _mainImage->setScaleImage(true);
    }
}

void ChoosePlayer::_mouse_click(EventReceiver &receiver, ITimer *timer)
{
    irr::core::vector2di pos = receiver.getCursorPos();
    int x = 3;

    if (receiver.isMouseLeftPressed() && _mouse == true) {
        while (pos.X < _pos[x].X && x > 0) {
            x--;
        }
        if (x == _where) {
            _check_arrow(pos, timer);
            return;
        }
        _where = x;
        _clear_display();
        return;
    }
    if (!receiver.isMouseLeftPressed()
    && (pressed_down == true || pressed_up == true)
    && keyboard_pressed == false) {
        pressed_down = false;
        pressed_up = false;
        _clear_display();
    }
}

void ChoosePlayer::_check_arrow(irr::core::vector2di pos, ITimer *timer)
{
    static int last = 0;

    if (timer->getTime() - last > 200) {
        if (pos.X >= _pos[_where].X + 100 && pos.Y >= _pos[_where].Y + 20
        && pos.X <= _pos[_where].X + 230 && pos.Y <= _pos[_where].Y + 106) {
            _choice[_where] = (_choice[_where] + 7) % 6;
            pressed_up = true;
            _clear_display();
        } else if (pos.X >= _pos[_where].X + 100 && pos.Y >= _pos[_where].Y + 200
        && pos.X <= _pos[_where].X + 230 && pos.Y <= _pos[_where].Y + 286) {
            _choice[_where] = (_choice[_where] + 5) % 6;
            pressed_down = true;
            _clear_display();
        }
        last = timer->getTime();
    }
}

void ChoosePlayer::_clear_display()
{
    _context->guienv->clear();
    draw();
}

void ChoosePlayer::_reinit()
{
    _where = 0;
    pressed_up = false;
    pressed_down = false;
    keyboard_pressed = false;
    echap = false;
    _mouse = false;
}
