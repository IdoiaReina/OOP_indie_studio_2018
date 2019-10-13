/*
** EPITECH PROJECT, 2019
** MapStock.cpp
** File description:
** MapStock class implementation
*/

#include "MapStock.hpp"

MapStock::MapStock(video::IVideoDriver *vidriver, scene::ISceneManager *scenemgr)
{
    this->init(vidriver, scenemgr);
}

MapStock::MapStock()
{
    // need to call a init after
}

MapStock::~MapStock()
{
}

void MapStock::init(video::IVideoDriver *vidriver, scene::ISceneManager *scenemgr)
{
    _vidriver = vidriver;
    _scenemgr = scenemgr;
    _map_stock[RANDOM_SMALL] = std::make_shared<RandomMap>(SMALL, _scenemgr, _vidriver, "./assets/maps/map_random1.txt");
    _map_stock[RANDOM_MEDIUM] = std::make_shared<RandomMap>(MEDIUM, _scenemgr, _vidriver, "./assets/maps/map_random2.txt");
    _map_stock[RANDOM_LARGE] = std::make_shared<RandomMap>(LARGE, _scenemgr, _vidriver, "./assets/maps/map_random3.txt");
    _map_stock[DONE_SMALL_1] = std::make_shared<DoneMap>(SMALL, _scenemgr, _vidriver, "./assets/maps/map1.1.txt");
    _map_stock[DONE_SMALL_2] = std::make_shared<DoneMap>(SMALL, _scenemgr, _vidriver, "./assets/maps/map1.2.txt");
    _map_stock[DONE_MEDIUM_1] = std::make_shared<DoneMap>(MEDIUM, _scenemgr, _vidriver, "./assets/maps/map2.2.txt");
    _map_stock[DONE_MEDIUM_2] = std::make_shared<DoneMap>(MEDIUM, _scenemgr, _vidriver, "./assets/maps/map2.3.txt");
    _map_stock[DONE_LARGE_1] = std::make_shared<DoneMap>(LARGE, _scenemgr, _vidriver, "./assets/maps/map3.1.txt");
    _map_stock[DONE_LARGE_2] = std::make_shared<DoneMap>(LARGE, _scenemgr, _vidriver, "./assets/maps/map3.3.txt");
}

std::shared_ptr<IMap> &MapStock::getMap(MapID id)
{
    if (id > _map_stock.size())
	throw GameException("Wrong map index");
    return _map_stock[id];
}
