/*
** EPITECH PROJECT, 2019
** ExplosionParticles.hpp
** File description:
** ExplosionParticles class definition
*/

#ifndef EXPLOSIONPARTICLES_HPP_
#define EXPLOSIONPARTICLES_HPP_

#include <irrlicht.h>
#include <iostream>

using namespace irr;

class ExplosionParticles
{
private:
    scene::ISceneManager *_scenemgr = nullptr;
    video::IVideoDriver *_vidriver = nullptr;

    video::ITexture *_fire = nullptr;
    scene::ISceneNode *_node = nullptr;
    scene::IParticleBoxEmitter * _emitter = nullptr;
    scene::IParticleSystemSceneNode * _psystem = nullptr;
    scene::IParticleFadeOutAffector *_affector = nullptr;

    core::vector3df _pos;

    void boom();
public:
    ExplosionParticles(scene::ISceneManager *, video::IVideoDriver *, core::vector3df, scene::ISceneNode *);
    ~ExplosionParticles();

    void unBoom();
    core::vector3df &getPosition();
    core::aabbox3df getBox();
};

#endif
