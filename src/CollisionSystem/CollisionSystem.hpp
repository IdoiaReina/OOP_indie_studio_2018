/*
** EPITECH PROJECT, 2019
** CollisionSystem.hpp
** File description:
** CollisionSystem class definition
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include <irrlicht.h>
#include <vector>
#include <string>

#include "MapGenerator.hpp"

using namespace irr;

class CollisionSystem
{
public:
    bool collide_X(scene::ISceneNode *, std::vector<std::string>, float);
    bool collide_Z(scene::ISceneNode *, std::vector<std::string>, float);
    bool collide(std::vector<scene::ISceneNode *> &, core::vector3df &, elemType);
    bool collide(scene::ISceneNode *, scene::ISceneNode *);
    bool collide(scene::ISceneNode *, core::vector3df &);
    bool collide(core::aabbox3df, core::vector3df &, scene::ISceneNode *);
    bool destroyable_Z(scene::ISceneNode *node1, std::vector<std::string> map, float move);
    bool destroyable_X(scene::ISceneNode *node1, std::vector<std::string> map, float move);
};

#endif