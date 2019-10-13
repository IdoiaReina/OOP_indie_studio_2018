/*
** EPITECH PROJECT, 2019
** MapStock.hpp
** File description:
** MapStock class definition
*/

#ifndef MAPSTOCK_HPP_
#define MAPSTOCK_HPP_

#include <irrlicht.h>
#include <memory>
#include <map>
#include <vector>

#include "GameException.hpp"

/* All maps */
#include "RandomMap.hpp"
#include "DoneMap.hpp"

using namespace irr;

class MapStock
{
private:
    std::map<MapID, std::shared_ptr<IMap>> _map_stock;
    video::IVideoDriver *_vidriver = nullptr;
    scene::ISceneManager *_scenemgr = nullptr;
public:
    MapStock(video::IVideoDriver *, scene::ISceneManager *);
    MapStock();
    ~MapStock();

    void init(video::IVideoDriver *, scene::ISceneManager *);
    std::shared_ptr<IMap> &getMap(MapID = RANDOM_MEDIUM);
};

#endif
