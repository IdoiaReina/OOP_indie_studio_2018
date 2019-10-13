/*
** EPITECH PROJECT, 2019
** RandomMap.hpp
** File description:
** RandomMap class definition
*/

#ifndef RANDOMMAP_HPP_
#define RANDOMMAP_HPP_

#include <iostream>
#include <fstream>
#include <algorithm>

#include "IMap.hpp"
#include "MapGenerator.hpp"

// Faire un getter de position pour dans le jeu savoir où sont les power-ups

class RandomMap : public IMap
{
private:
    scene::ISceneManager *_scenemgr = nullptr;
    video::IVideoDriver *_vidriver = nullptr;

    scene::ISceneNode *_node = nullptr;

    u32 _length;
    u32 _width;
    mapSize _size = MEDIUM;
    
    void setMapSize(mapSize);

    MapGenerator _generator;
    std::vector<core::vector3d<float>> _indestructibleBlocksPos;
    std::vector<core::vector3d<float>> _destructibleBlocksPos;
    std::vector<core::vector3d<float>> _powerUpBlocksPos;
    std::vector<scene::ISceneNode *> _indestructibleBlocksMesh;
    std::vector<scene::ISceneNode *> _destructibleBlocksMesh;
    std::vector<scene::ISceneNode *> _powerUpBlocksMesh;
    std::vector<scene::ISceneNode *> _ground;
    std::vector<scene::ISceneNode *> _all;

    std::string _name;
    std::vector<std::string> _map;

    void readMapFromFile();
    void create_ground();
    void create_indestrutible();
    void create_destrutible();
    void create_powerup();
public:
    RandomMap(mapSize, scene::ISceneManager *, video::IVideoDriver *, std::string);
    ~RandomMap() final;

    void create() final;
    void destroy() final;
    mapSize getMapSize() const final;
    std::vector<std::string> &getMap() final;
    std::vector<scene::ISceneNode *> &getModels() final;
};

#endif
