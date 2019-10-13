/*
** EPITECH PROJECT, 2019
** Indie.cpp
** File description:
** Indie class implementation
*/

#include "Indie.hpp"

Indie::Indie()
{
    _device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(1920,1080), 16, true, false, true, &_receiver);
    _context.vidriver = _device->getVideoDriver();
    _context.scenemgr = _device->getSceneManager();
    _context.guienv = _device->getGUIEnvironment();
    _context.scenemgr->setAmbientLight(video::SColorf(0.8f,0.8f,0.8f,0.8f));
    _timer = _device->getTimer();
    _cursor = _device->getCursorControl();
    _receiver.setCursorControl(_cursor);
    _device->setWindowCaption(L"The Legend Of Bomberman!");
    _scenes.init(&_context);
}

Indie::~Indie()
{
    _device->drop();
}

void Indie::event()
{
    SceneID shown = _shown;

    _scenes.event_scene(_receiver, _timer, shown);
    if (shown == CLOSE_SCENE) {
        _device->closeDevice();
    } else if (shown != _shown) {
        _shown = shown;
        _scenes.change_scene(_shown);
    }
}

void Indie::letsgo()
{
    while (_device->run() && _context.vidriver) {
        this->event();
        _context.vidriver->beginScene(true, true, video::SColor(255, 100, 100, 140));
        _context.scenemgr->drawAll();
        _context.guienv->drawAll();
        _context.vidriver->endScene();
    }
    return;
}
