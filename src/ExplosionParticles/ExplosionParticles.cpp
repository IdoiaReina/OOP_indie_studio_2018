/*
** EPITECH PROJECT, 2019
** ExplosionParticles.cpp
** File description:
** ExplosionParticles class implementation
*/

#include "ExplosionParticles.hpp"

ExplosionParticles::ExplosionParticles(scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, core::vector3df pos, scene::ISceneNode *node)
{
    _scenemgr = scenemgr;
    _vidriver = vidriver;
    _node = node;
    _fire = _vidriver->getTexture("./assets/fire.png");
    _pos = pos;
    this->boom();
}

ExplosionParticles::~ExplosionParticles()
{
}

void ExplosionParticles::boom()
{
    _psystem = _scenemgr->addParticleSystemSceneNode(false, _node);
    _affector = _psystem->createFadeOutParticleAffector();
    _affector->setFadeOutTime(80);
    _emitter = _psystem->createBoxEmitter(
	core::aabbox3d<f32>(-1,0,-0.775,1,2,0.775), // emitter size
        core::vector3df(0.0f,0.01f,0.0f),           // initial direction
        100, 120,                                   // emit rate
        video::SColor(0,255,255,255),               // darkest color
        video::SColor(0,255,255,255),               // brightest color
        20,80,0,                                  // min and max age, angle
        core::dimension2df(0.5f,0.5f),              // min size
        core::dimension2df(2.f,2.f));               // max size
    _psystem->setEmitter(_emitter);
    _psystem->addAffector(_affector);
    _psystem->setPosition(_pos);
    _psystem->setMaterialFlag(video::EMF_LIGHTING, false);
    _psystem->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    _psystem->setMaterialTexture(0, _fire);
    _psystem->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    _affector->drop();
    _affector = nullptr;
}

void ExplosionParticles::unBoom()
{
    _emitter->drop();
    _emitter = nullptr;
    _psystem->remove();
}

core::vector3df &ExplosionParticles::getPosition()
{
    return _pos;
}

core::aabbox3df ExplosionParticles::getBox()
{
    return _emitter->getBox();
}
