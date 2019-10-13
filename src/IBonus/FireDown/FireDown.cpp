/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** FireDown
*/

#include "FireDown.hpp"

FireDown::FireDown(scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node, core::vector3df &pos)
{
    _node = node;
    _scenemgr = scenemgr;
    _vidriver = vidriver;
    _pos = pos;
    _skin = vidriver->getTexture("./models/bonus/fire_down.png");
    _model = _scenemgr->getMesh("./models/bonus/item.b3d");
    _model->setHardwareMappingHint(scene::EHM_STATIC);
    _spawn = std::chrono::high_resolution_clock::now();
    this->create();
}

FireDown::~FireDown()
{
}

void FireDown::effect(std::unique_ptr<APlayer> &player)
{
    player->lessRange();
}

void FireDown::create()
{
    _mesh = _scenemgr->addAnimatedMeshSceneNode(_model, _node);
    _mesh->setPosition(_pos);
    _mesh->setRotation(core::vector3df(0, 180, 0));
    _mesh->setScale(core::vector3df(0.8f, 0.8f, 0.8f));
    _mesh->setMaterialTexture(0, _skin);
    _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
}

void FireDown::destroy()
{
    _mesh->remove();
}

scene::ISceneNode *FireDown::getModel() const
{
    return _mesh;
}

bool FireDown::isDestructible()
{
    _stop = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration<double, std::milli>(_stop - _spawn).count() >= 1500);
}
