/*
** EPITECH PROJECT, 2019
** Menu.cpp
** File description:
** Menu class implementation
*/

#include "Menu.hpp"

using namespace irr;
using namespace gui;

Menu::Menu(AppContext *context)
{
    _context = context;
    _node = _context->scenemgr->addEmptySceneNode();
    _back = _context->vidriver->getTexture("./assets/back.png");
    _play_button = _context->vidriver->getTexture("./assets/play.png");
    _play_button_pressed = _context->vidriver->getTexture("./assets/play_pressed.png");
    _settings_button = _context->vidriver->getTexture("./assets/settings.png");
    _settings_button_pressed = _context->vidriver->getTexture("./assets/settings_pressed.png");
    _load_button = _context->vidriver->getTexture("./assets/load.png");
    _load_button_pressed = _context->vidriver->getTexture("./assets/load_pressed.png");
    _quit_button = _context->vidriver->getTexture("./assets/quit.png");
    _quit_button_pressed = _context->vidriver->getTexture("./assets/quit_pressed.png");
//    _musicManager.setMusic("./assets/musics/menu.ogg");
}

Menu::~Menu()
{
}

void Menu::setButtonNorm(gui::IGUIButton *button)
{
    button->setScaleImage(true);
    button->setUseAlphaChannel(true);
    button->setDrawBorder(false);
}

void Menu::draw()
{
//    this->_musicManager.playMusic();
    _guiBack = _context->guienv->addImage(core::rect<s32>(0,0,1920,1080));
    _guiBack->setImage(_back);
    _guiBack->setScaleImage(true);
    _play = _context->guienv->addButton(core::rect<s32>(500,450,850,550), 0, PLAY_BUTTON);
    _play->setImage(_play_button);
    _play->setPressedImage(_play_button_pressed);
    this->setButtonNorm(_play);
    _settings = _context->guienv->addButton(core::rect<s32>(750,650,1150,750), 0, SETTINGS_BUTTON);
    _settings->setImage(_settings_button);
    _settings->setPressedImage(_settings_button_pressed);
    this->setButtonNorm(_settings);
    _quit = _context->guienv->addButton(core::rect<s32>(750,850,1150,950), 0, QUIT_BUTTON);
    _quit->setImage(_quit_button);
    _quit->setPressedImage(_quit_button_pressed);
    this->setButtonNorm(_quit);
    _load = _context->guienv->addButton(core::rect<s32>(1050,450,1400,550), 0, LOAD_BUTTON);
    _load->setImage(_load_button);
    _load->setPressedImage(_load_button_pressed);
    this->setButtonNorm(_load);
    _drawn = true;
}

void Menu::destroy()
{
    _node->removeAll();
    _context->guienv->clear();
    _drawn = false;
//    this->_musicManager.stopMusic();
}

void Menu::event(EventReceiver &receiver, ITimer *timer, SceneID &shown)
{
    if (receiver.isLoadable() == true)
        _save->loadFile(_context, receiver.getLoadPath());
    if (_play->isPressed())
        shown = CHOOSEPLAYER_SCENE;
    if (_settings->isPressed())
        shown = SETTINGS_SCENE;
    if (receiver.isKeyDown(irr::KEY_KEY_E) && shown < 1)
        shown = SETTINGS_SCENE;
    if (_quit->isPressed())
        shown = CLOSE_SCENE;
    if (_load->isPressed()) {
        _save->loadButton(_context);
    }
}
