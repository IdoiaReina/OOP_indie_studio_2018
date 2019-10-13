/*
** EPITECH PROJECT, 2019
** RandomMap.cpp
** File description:
** RandomMap class implementation
*/

#include "RandomMap.hpp"

RandomMap::RandomMap(mapSize size, scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, std::string name)
    : _generator(size, name)
{
    _name = name;
    _scenemgr = scenemgr;
    _vidriver = vidriver;
    _node = scenemgr->addEmptySceneNode();
    _size = size;
    this->setMapSize(size);
}

RandomMap::~RandomMap()
{
    _all.clear();
    _indestructibleBlocksPos.clear();
    _indestructibleBlocksMesh.clear();
    _destructibleBlocksPos.clear();
    _destructibleBlocksMesh.clear();
    _powerUpBlocksPos.clear();
    _powerUpBlocksMesh.clear();
}

void RandomMap::setMapSize(mapSize size)
{
    if (size == SMALL) {
        _length = 11;
        _width = 9;
    }
    else if (size == MEDIUM) {
        _length = 15;
        _width = 13;
    }
    else {
        _length = 19;
        _width = 17;
    }
}

void RandomMap::create_indestrutible()
{
    scene::IAnimatedMeshSceneNode *tmp = nullptr;
    auto itIndestructible = _indestructibleBlocksPos.begin();

    while (itIndestructible != _indestructibleBlocksPos.end()) {
        tmp = _scenemgr->addAnimatedMeshSceneNode(_scenemgr->getMesh("./models/box/box.x"), _node, INDESTRUCTIBLE);
	tmp->getMesh()->setHardwareMappingHint(scene::EHM_STATIC);
        tmp->setMaterialFlag(video::EMF_LIGHTING, false);
        tmp->setMaterialTexture(0, _vidriver->getTexture("./models/box/metal.png"));
        tmp->setPosition(*itIndestructible);
        _indestructibleBlocksMesh.push_back(tmp);
	_all.push_back(tmp);
        ++itIndestructible;
    }
}

void RandomMap::create_destrutible()
{
    scene::IAnimatedMeshSceneNode *tmp = nullptr;
    auto itDestructible = _destructibleBlocksPos.begin();

    while (itDestructible != _destructibleBlocksPos.end()) {
        tmp = _scenemgr->addAnimatedMeshSceneNode(_scenemgr->getMesh("./models/box/box.x"), _node, DESTRUCTIBLE);
	tmp->getMesh()->setHardwareMappingHint(scene::EHM_STATIC);
        tmp->setMaterialFlag(video::EMF_LIGHTING, false);
        tmp->setMaterialTexture(0, _vidriver->getTexture("./models/box/wood.png"));
        tmp->setPosition(*itDestructible);
        _destructibleBlocksMesh.push_back(tmp);
	_all.push_back(tmp);
        ++itDestructible;
   }
}

void RandomMap::create_powerup()
{
    scene::IAnimatedMeshSceneNode *tmp = nullptr;
    auto itPowerUp = _powerUpBlocksPos.begin();

    while (itPowerUp != _powerUpBlocksPos.end()) {
        tmp = _scenemgr->addAnimatedMeshSceneNode(_scenemgr->getMesh("./models/box/box.x"), _node, POWER_UP);
	tmp->getMesh()->setHardwareMappingHint(scene::EHM_STATIC);
        tmp->setMaterialFlag(video::EMF_LIGHTING, false);
        tmp->setMaterialTexture(0, _vidriver->getTexture("./models/box/wood.png"));
        tmp->setPosition(*itPowerUp);
        _powerUpBlocksMesh.push_back(tmp);
	_all.push_back(tmp);
        ++itPowerUp;
    }
}

static std::vector<std::string> rotate_map(std::vector<std::string> &_map)
{
    int column = _map.size();
    int line = -1;
    std::vector<std::string> to_return;
    std::string line_ = "";

    while (++line != _map[0].size()) {
        while (--column != -1) {
            line_ += _map[column][line];
        }
        column = _map.size();
        reverse(line_.begin(), line_.end());
        to_return.push_back(line_);
        line_ = "";
    }
    _map.clear();
    return to_return;
}

void RandomMap::readMapFromFile()
{
    std::ifstream file(_name);
    std::string line;

    _map.clear();
    while (std::getline(file, line)) {
        _map.push_back(line);
    }
    _map = rotate_map(_map);
    file.close();
}

std::vector<std::string> &RandomMap::getMap()
{
    return _map;
}

std::vector<scene::ISceneNode *> &RandomMap::getModels()
{
    return _all;
}

void RandomMap::create()
{
    _all.clear();
    _indestructibleBlocksPos.clear();
    _indestructibleBlocksMesh.clear();
    _destructibleBlocksPos.clear();
    _destructibleBlocksMesh.clear();
    _powerUpBlocksPos.clear();
    _powerUpBlocksMesh.clear();
    _generator.startGeneration();
    _indestructibleBlocksPos = _generator.getElemVector3d(INDESTRUCTIBLE);
    _destructibleBlocksPos = _generator.getElemVector3d(DESTRUCTIBLE);
    _powerUpBlocksPos = _generator.getElemVector3d(POWER_UP);
    this->readMapFromFile();
    this->create_ground();
    this->create_indestrutible();
    this->create_destrutible();
    this->create_powerup();
}

void RandomMap::create_ground()
{
    core::vector3df pos;
    scene::IAnimatedMeshSceneNode *tmp = nullptr;
    u32 x = 0;
    u32 y = 0;

    while (x != (_length - 2)) {
        y = 0;
        while (y != (_width + 2)) {
            pos.X = x * 2;
            pos.Y = -2;
            pos.Z = y * 1.55;
            tmp = _scenemgr->addAnimatedMeshSceneNode(_scenemgr->getMesh("./models/box/box.x"), _node);
	    tmp->getMesh()->setHardwareMappingHint(scene::EHM_STATIC);
            tmp->setMaterialFlag(video::EMF_LIGHTING, false);
            tmp->setMaterialTexture(0, _vidriver->getTexture("./models/box/ground.png"));
            tmp->setPosition(pos);
            _ground.push_back(tmp);
            ++y;
        }
        ++x;
    }
}

mapSize RandomMap::getMapSize() const
{
    return _size;
}

void RandomMap::destroy()
{
    _node->removeAll();
}
