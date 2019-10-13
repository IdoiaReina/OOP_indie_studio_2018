/*
** EPITECH PROJECT, 2018
** MapSelector.cpp
** File description:
** MapSelector class implementation
*/

#include <iostream>
#include "MapSelector.hpp"

MapSelector::MapSelector(AppContext *context)
{
    _context = context;
    _node = _context->scenemgr->addEmptySceneNode();
    _back = _context->vidriver->getTexture("./assets/back1.png");
    _bordure_name = _context->vidriver->getTexture("./assets/name.png");
    _cadre = _context->vidriver->getTexture("./assets/map_cadre.png");
    _selected = _context->vidriver->getTexture("./assets/selected.png");
    _locked = _context->vidriver->getTexture("./assets/locker.png");
//    _musicManager.setMusic("./assets/musics/selection_perso.ogg");
    _fill_vector("./assets/map_selection/map/", _map);
    _fill_vector("./assets/map_selection/", _name);
}

MapSelector::~MapSelector()
{
}

void MapSelector::_fill_vector(std::string _path, std::vector<video::ITexture *> &to_fill)
{
    to_fill.push_back(_context->vidriver->getTexture((_path + "randomsmall.png").c_str()));
    to_fill.push_back(_context->vidriver->getTexture((_path + "dix secondes de plaisir.png").c_str()));
    to_fill.push_back(_context->vidriver->getTexture((_path + "la classico.png").c_str()));
    to_fill.push_back(_context->vidriver->getTexture((_path + "randommedium.png").c_str()));
    to_fill.push_back(_context->vidriver->getTexture((_path + "gg ez noob.png").c_str()));
    to_fill.push_back(_context->vidriver->getTexture((_path + "le damier.png").c_str()));
    to_fill.push_back(_context->vidriver->getTexture((_path + "randomlarge.png").c_str()));
    to_fill.push_back(_context->vidriver->getTexture((_path + "bloc sur 20.png").c_str()));
    to_fill.push_back(_context->vidriver->getTexture((_path + "triforce de ses morts.png").c_str()));
}

void MapSelector::draw()
{
//    _musicManager.playMusic();
    _backI = _context->guienv->addImage(core::rect<s32>(0, 0, 1920, 1080));
    _backI->setImage(_back);
    _backI->setScaleImage(true);
    _context->guienv->addImage(_bordure_name, core::position2d<int>(115,50));
    _draw_cadre();
    _print_map_vector();
    _nameI = _context->guienv->addImage(core::rect<s32>(132, 90, 798, 164));
    _nameI->setImage(_name[map_selected]);
    _nameI->setScaleImage(true);
    if (selected == false) {
        _selectedI = _context->guienv->addImage(core::rect<s32>(selected_x, selected_y, (selected_x + 190), (selected_y + 100)));
        _selectedI->setImage(_selected);
        _selectedI->setScaleImage(true);
    } else {
        _lockedI = _context->guienv->addImage(core::rect<s32>(selected_x + 40, selected_y + 60, (selected_x + 140), (selected_y + 160)));
        _lockedI->setImage(_locked);
        _lockedI->setScaleImage(true);
    }
}

void MapSelector::_print_map_vector()
{
    int line = -1;
    int col = -1;
    int x = 65;
    int y = 270;
    int button_num = 0;

    while (++col != 3) {
        while (++line != 3) {
            _cadreI = _context->guienv->addImage(core::rect<s32>(x, y, (x + 220), (y + 160)));
            _cadreI->setImage(_map[button_num]);
            _cadreI->setScaleImage(true);
            x += 300;
            button_num += 1;
        }
        y += 250;
        x = 65;
        line = -1;
    }
    _context->guienv->addImage(_map[map_selected], core::position2d<int>(950,200));
}

void MapSelector::destroy()
{
//    _musicManager.stopMusic();
    _map.clear();
    _name.clear();
    _node->removeAll();
    _context->guienv->clear();
}

void MapSelector::lock_enter(EventReceiver &receiver, ITimer *timer)
{
    static int last = 0;

    if (receiver.isKeyDown(irr::KEY_RETURN) == false)
        enter = true;
    if (receiver.isKeyDown(irr::KEY_RETURN)
    && selected != true && timer->getTime() - last > 200
    && enter == true) {
        last = timer->getTime();
        selected = true;
        update_pos();
        selected_lock = timer->getTime();
    }
    if (receiver.isKeyDown(irr::KEY_RETURN)
    && selected == true && timer->getTime() - last > 200
    && enter == true) {
        last = timer->getTime();
        selected = false;
        update_pos();
    }
}

void MapSelector::event(EventReceiver &receiver, ITimer *timer,  SceneID &shown)
{
    static int last = 0;

    mouse_clic(receiver, timer);
    lock_enter(receiver, timer);
    if (selected == false) {
        selected_map(receiver, timer);
    }
    if (receiver.isKeyDown(irr::KEY_ESCAPE)
    && timer->getTime() - last > 200) {
        last = timer->getTime();
        shown = CHOOSEPLAYER_SCENE;
        reinit();
    }
    if (selected == true && timer->getTime() - selected_lock > 3000) {
        _context->map = (MapID)map_selected;
        shown = GAME_SCENE;
        reinit();
    }
}

void MapSelector::_draw_cadre()
{
    int line = -1;
    int col = -1;
    int x = 50;
    int y = 250;

    while (++col != 3) {
        while (++line != 3) {
            _cadreI = _context->guienv->addImage(core::rect<s32>(x, y, (x + 250), (y + 200)));
            _cadreI->setImage(_cadre);
            _cadreI->setScaleImage(true);
            x += 300;
        }
        y += 250;
        x = 50;
        line = -1;
    }
}

void MapSelector::selected_map(EventReceiver &receiver, ITimer *timer)
{
    static int time = 0;
    int actual = timer->getTime();
    int arrow = 36;
    bool change_selected = false;

    while (++arrow != 41) {
        if (receiver.isKeyDown((EKEY_CODE)arrow) && actual - time > 200) {
            time = timer->getTime();
            if (arrow % 2 == 1)
                col = ((col + (arrow - 38)) + 3) % 3;
            else
                line = ((line + (arrow - 39)) + 3) % 3;
            update_pos();
        }
    }
    return;
}

bool MapSelector::in_cadre(EventReceiver &receiver, irr::core::vector2di pos)
{
    int x = pos.X - 50;
    int y = pos.Y - 250;
    int nbr_w_size = x / 300;
    int nbr_h_size = y / 250;

    if (((x - (nbr_w_size * 250)) - (nbr_w_size * 50)) >= 250
    || ((y - (nbr_h_size * 200)) - (nbr_h_size * 50)) >= 200
    || nbr_w_size > 2 || pos.Y < 250
    || nbr_h_size > 2 || pos.X < 50)
        return false;
    return true;
}

void MapSelector::mouse_clic(EventReceiver &receiver, ITimer *timer)
{
    irr::core::vector2di pos = receiver.getCursorPos();
    static int last_time = 0;
    static bool clicked = false;

    if (receiver.isMouseLeftPressed() && clicked == false
    && in_cadre(receiver, pos)) {
        clicked = true;
        if ((pos.X - 50) / 300 == col && (pos.Y - 250) / 250 == line
        && timer->getTime() - last_time < 200) {
            selected = (selected + 1) % 2;
            selected_lock = timer->getTime();
            update_pos();
            return;
        }
        if (selected == true)
            return;
        col = (pos.X - 50) / 300;
        line = (pos.Y - 250) / 250;
        update_pos();
        return;
    }
    if (clicked == true
    && !receiver.isMouseLeftPressed()) {
        clicked = false;
        last_time = timer->getTime();
    }
    return;
}

void MapSelector::update_pos()
{
    selected_x = 80 + (300 * col);
    selected_y = 325 + (250 * line);
    map_selected = line * 3 + col;
    clear_display();
}

void MapSelector::reinit()
{
    selected_x = 80;
    selected_y = 325;
    map_selected = 0;
    col = 0;
    line = 0;
    selected = false;
    enter = false;
    selected_lock = 0;
    clear_display();
}

void MapSelector::clear_display()
{
    _context->guienv->clear();
    draw();
}