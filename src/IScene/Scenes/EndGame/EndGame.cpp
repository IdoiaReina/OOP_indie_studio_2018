/*
** EPITECH PROJECT, 2018
** EndGame.cpp
** File description:
** EndGame class implementation
*/

#include <iostream>
#include "EndGame.hpp"

EndGame::EndGame(AppContext *context)
{
    _context = context;
    _node = _context->scenemgr->addEmptySceneNode();
    _back = _context->vidriver->getTexture("./assets/back1.png");
    _change_map = _context->vidriver->getTexture("./assets/change_map.png");
    _change_player = _context->vidriver->getTexture("./assets/change_player.png");
    _menu = _context->vidriver->getTexture("./assets/menu.png");
    _file_vector();
//    _musicManager.setMusic("./assets/musics/selection_perso.ogg");
}

EndGame::~EndGame()
{
}

void EndGame::_file_vector()
{
    _pos.push_back({400, 600});
    _pos.push_back({1200, 600});
    _pos.push_back({800, 800});
}

void EndGame::draw()
{
//    _musicManager.playMusic();
    _winner = _context->winner;
    _win = _context->vidriver->getTexture(("./assets/pw" + std::to_string(_winner) +".png").c_str());
    _mainImage = _context->guienv->addImage(core::rect<s32>(0, 0, 1920, 1080));
    _mainImage->setImage(_back);
    _mainImage->setScaleImage(true);
    _context->guienv->addImage(_win, core::position2d<int>(600, 0));
    _draw_button();
}

void EndGame::destroy()
{
    _node->removeAll();
    _context->guienv->clear();
    _pos.clear();
//    _musicManager.stopMusic();
}

void EndGame::event(EventReceiver &receiver, ITimer *timer,  SceneID &shown)
{
    button = 3;
    _mouse_click(receiver, timer);
    if (button == 0) {
        shown = CHOOSEPLAYER_SCENE;
    } else if (button == 1) {
        shown = MAPSELECTOR_SCENE;
    } else if (button == 2) {
        shown = MENU_SCENE;
    }
}

void EndGame::_draw_button()
{
    _mainImage = _context->guienv->addImage({_pos[0].X, _pos[0].Y, _pos[0].X + 300, _pos[0].Y + 100});
    _mainImage->setImage(_change_player);
    _mainImage->setScaleImage(true);
    _mainImage = _context->guienv->addImage({_pos[1].X, _pos[1].Y, _pos[1].X + 300, _pos[1].Y + 100});
    _mainImage->setImage(_change_map);
    _mainImage->setScaleImage(true);
    _mainImage = _context->guienv->addImage({_pos[2].X, _pos[2].Y, _pos[2].X + 300, _pos[2].Y + 100});
    _mainImage->setImage(_menu);
    _mainImage->setScaleImage(true);
}

static bool compare(irr::core::vector2di _pos, irr::core::vector2di mouse)
{
    if (mouse.X >= _pos.X && mouse.X <= _pos.X + 300
    && mouse.Y >= _pos.Y && mouse.Y <= _pos.Y + 100)
        return true;
    return false;
}

void EndGame::_mouse_click(EventReceiver &receiver, ITimer *timer)
{
    irr::core::vector2di pos = receiver.getCursorPos();
    int itt = -1;

    if (receiver.isMouseLeftPressed()) {
        while (++itt != 3 && !compare(_pos[itt], pos));
        button = itt;
    }
}

void EndGame::_clear_display()
{
    _context->guienv->clear();
    draw();
}
