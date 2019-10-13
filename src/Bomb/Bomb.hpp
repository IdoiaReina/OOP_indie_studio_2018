/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <irrlicht.h>
#include <vector>
#include <iostream>

#include "ExplosionParticles.hpp"
#include "CollisionSystem.hpp"
#include "MapGenerator.hpp"

using namespace irr;

class Bomb {
public:
    Bomb(scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node, int range, const core::vector3df &pos, ITimer *timer);
    ~Bomb();

    bool isBooming();
    bool isEnded();
    void explodeMaybe();
    void setPiercing(bool isPiercing);
    std::vector<ExplosionParticles> &getExplosionParticles();
    void explode(std::vector<scene::ISceneNode *> &);
    void forceBooming();
    scene::ISceneNode *getModel() const;
private:
    scene::ISceneNode *_node = nullptr;
    scene::ISceneManager *_scenemgr = nullptr;
    video::IVideoDriver *_vidriver = nullptr;

    CollisionSystem _col;

    video::ITexture *_skin = nullptr;
    scene::IAnimatedMesh *_model = nullptr;

    scene::IAnimatedMeshSceneNode *_mesh = nullptr;
    u32 compteARebour = 5000;
    ITimer *_timer;
    u32 _startTime;
    core::vector3df _pos;
    bool _isPiercing;
    int _range;
    bool _isExplode = false;
    bool _boom = false;

    std::vector<ExplosionParticles> _explosion;

    const u32 getElapsedTime();
    void explodeNorth(std::vector<scene::ISceneNode *> &);
    void explodeSouth(std::vector<scene::ISceneNode *> &);
    void explodeEast(std::vector<scene::ISceneNode *> &);
    void explodeWest(std::vector<scene::ISceneNode *> &);
};

#endif /* !BOMB_HPP_ */
