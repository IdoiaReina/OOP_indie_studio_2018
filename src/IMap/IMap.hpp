/*
** EPITECH PROJECT, 2019
** IMap.hpp
** File description:
** IMap class interface
*/

#ifndef IMAP_HPP_
#define IMAP_HPP_

#include <irrlicht.h>

#include "MapGenerator.hpp"

using namespace irr;

enum MapID {
    NOT_SELECTED = -1,
    RANDOM_SMALL = 0,
    RANDOM_MEDIUM = 3,
    RANDOM_LARGE = 6,
    DONE_SMALL_1 = 1,
    DONE_SMALL_2 = 2,
    DONE_MEDIUM_1 = 4,
    DONE_MEDIUM_2 = 5,
    DONE_LARGE_1 = 7,
    DONE_LARGE_2 = 8,
};

class IMap
{
public:
    virtual ~IMap() = default;

    virtual void create() = 0;
    virtual void destroy() = 0;
    virtual mapSize getMapSize() const = 0;
    virtual std::vector<std::string> &getMap() = 0;
    virtual std::vector<scene::ISceneNode *> &getModels() = 0;
};

#endif
