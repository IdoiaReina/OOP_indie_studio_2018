/*
** EPITECH PROJECT, 2019
** MapGenerator
** File description:
** MapGenerator
*/

/**
 * @file MapGenerator.hpp
 * @author Thomas LESUEUR (thomas.lesueur@epitech.eu)
 * @brief file which contain MapGenerator class definition
 * @version 0.1
 * @date 2019-06-13
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef MAPGENERATOR_HPP_
#define MAPGENERATOR_HPP_

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <irrlicht.h>
#include <ctime>
#include <queue>
#include <sstream>

enum spawnRate {
    NONE,
    LITTLE,
    NORMAL,
    HIGH
};

enum mapSize {
    SMALL,
    MEDIUM,
    LARGE
};

enum elemType {
    INDESTRUCTIBLE,
    DESTRUCTIBLE,
    POWER_UP,
    UNKNOWN
};

/**
 * @brief MapGenerator class
 *
 */
class MapGenerator {
public:
    MapGenerator();
    MapGenerator(mapSize size, std::string &name, spawnRate powerUpSpawnRate = NORMAL, spawnRate blockRate = NORMAL);
    ~MapGenerator();

    void startGeneration();
    void writeInfile();
    void setMapSize(mapSize size);
    void setBlockRate(spawnRate rate);
    void setPowerUpRate(spawnRate rate);
    char chooseElement();
    char choosePowerUp();
    const std::queue<unsigned int> getMapDimension() const;
    const std::vector<irr::core::vector3d<float>> &getElemVector3d(elemType type) const;
    void mapTxtToVector(std::string path);

private:
    std::string _name;
    unsigned int _length;
    unsigned int _width;
    float _blockRate;
    float _powerUpRate;
    std::vector<std::string> _map;
    std::vector<irr::core::vector3df> _indestructibleBlocksPos;
    std::vector<irr::core::vector3df> _destructibleBlocksPos;
    std::vector<irr::core::vector3df> _PowerUpBlocksPos;
    
    void createMidRows();
    void createEmptyRow();
    void createSingleRow();
    void createIndestructibleRow();
    void freePlayersSpawn();
    void getElemPos();
    void setVector3dPos(size_t x, size_t y, std::string elem);
    void getElemPosVector(std::string fileContent);
};

#endif /* !MAPGENERATOR_HPP_ */
