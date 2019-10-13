/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** DoneMap
*/

#ifndef DONEMAP_HPP_
#define DONEMAP_HPP_

#include "IMap.hpp"
#include "MapGenerator.hpp"

class DoneMap : public IMap {
public:
    DoneMap(mapSize, scene::ISceneManager *, video::IVideoDriver *, std::string);
    ~DoneMap() final;

    void create() final;
    void destroy() final;
    mapSize getMapSize() const final;
    std::vector<std::string> &getMap() final;
    std::vector<scene::ISceneNode *> &getModels() final;

private:
    scene::ISceneManager *_scenemgr = nullptr;
    video::IVideoDriver *_vidriver = nullptr;

    scene::ISceneNode *_node = nullptr;

    u32 _length;
    u32 _width;
    mapSize _size = MEDIUM;

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

    MapGenerator _generator;

    void readMapFromFile();
    void createGround();
    void createIndestrutible();
    void createDestrutible();
    void createPowerup();
    void setMapSize(mapSize);
};

#endif /* !DONEMAP_HPP_ */
