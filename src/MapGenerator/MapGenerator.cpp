/*
** EPITECH PROJECT, 2019
** MapGenerator
** File description:
** MapGenerator
*/

/**
 * @file MapGenerator.cpp
 * @author Thomas LESUEUR (thomas.lesueur@epitech.eu)
 * @brief Contain MapGenerator member functions
 * @version 0.1
 * @date 2019-06-13
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "MapGenerator.hpp"

void MapGenerator::setMapSize(mapSize size)
{
    if (size == SMALL) {
        this->_length = 11;
        this->_width = 9;
    }
    else if (size == MEDIUM) {
        this->_length = 15;
        this->_width = 13;
    }
    else {
        this->_length = 19;
        this->_width = 17;
    }
}

void MapGenerator::setBlockRate(spawnRate rate)
{
    if (rate == NONE)
        this->_blockRate = 0;
    else if (rate == LITTLE)
        this->_blockRate = 0.13;
    else if (rate == NORMAL)
        this->_blockRate = 0.25;
    else
        this->_blockRate = 0.38;
}

void MapGenerator::setPowerUpRate(spawnRate rate)
{
    if (rate == NONE)
        this->_powerUpRate = 0;
    else if (rate == LITTLE)
        this->_powerUpRate = 0.13;
    else if (rate == NORMAL)
        this->_powerUpRate = 0.25;
    else
        this->_powerUpRate = 0.38;

}

/**
 * @brief Construct a new Map Generator:: Map Generator object
 *
 * @param size
 * @param powerUpSpawnRate
 * @param blockRate
 */

/**
 * @brief Construct a new Map Generator:: Map Generator object
 *
 * @param size
 * @param powerUpSpawnRate
 * @param blockRate
 */
MapGenerator::MapGenerator(mapSize size, std::string &name, spawnRate powerUpSpawnRate, spawnRate blockRate)
{
    std::srand(std::time(NULL));
    _name = name;
    setMapSize(size);
    setBlockRate(blockRate);
    setPowerUpRate(powerUpSpawnRate);
}

/**
 * @brief Construct a new Map Generator:: Map Generator object
 *
 */
MapGenerator::MapGenerator()
{
    srand(time(NULL));

    _name = "oupsi.txt";
    this->_length = 15;
    this->_width = 13;
    this->_powerUpRate = 0.25;
    this->_blockRate = 0.25;
}

/**
 * @brief Destroy the Map Generator:: Map Generator object
 *
 */
MapGenerator::~MapGenerator()
{
}

/**
 * @brief launch the generation of a new map
 *
 */
void MapGenerator::startGeneration()
{
    this->_map.clear();
    this->_destructibleBlocksPos.clear();
    this->_indestructibleBlocksPos.clear();
    this->_PowerUpBlocksPos.clear();
    createIndestructibleRow();
    createMidRows();
    createIndestructibleRow();
    freePlayersSpawn();
    writeInfile(); //uncomment to see map preview in map.txt
    getElemPos();
}

void MapGenerator::createIndestructibleRow()
{
    std::string line("", this->_length);

    std::fill(line.begin(), line.end(), '#');
    this->_map.push_back(line);
}

void MapGenerator::createEmptyRow()
{
    std::string line("", this->_length);

    std::fill(line.begin(), line.end(), ' ');
    line.front() = '#';
    line.back() = '#';
    for (size_t i = 0; i != this->_length - 1; i++)
        if (i != 0)
            line[i] = chooseElement();
    this->_map.push_back(line);
}

char MapGenerator::chooseElement()
{
    int blockRateLimit = this->_blockRate * 100;
    int powerUpRateLimit = blockRateLimit + this->_powerUpRate * 100;
    int randomNumber = rand() % 100 + 1;

    if (randomNumber <= blockRateLimit)
        return ('0');
    else if (randomNumber > blockRateLimit && randomNumber < powerUpRateLimit)
        return ('1');
    else
        return (' ');
}

void MapGenerator::createSingleRow()
{
    std::string line("", this->_length);

    std::fill(line.begin(), line.end(), '#');
    for (size_t j = 0; j != this->_length - 1; j++) {
        if (j % 2 == 1) {
            line[j] = chooseElement();
        }
    }
    this->_map.push_back(line);
}

void MapGenerator::createMidRows()
{
    for (size_t i = 0; i != this->_width - 2; i++) {
        if (i % 2 == 1)
            createSingleRow();
        else
            createEmptyRow();
    }
}

/**
 * @brief free space for player spawning area
 *
 */
void MapGenerator::freePlayersSpawn()
{
    this->_map[1][1] = ' ';
    this->_map[1][2] = ' ';
    this->_map[2][1] = ' ';
    this->_map[1][this->_length - 2] = ' ';
    this->_map[2][this->_length - 2] = ' ';
    this->_map[1][this->_length - 3] = ' ';

    this->_map[this->_width - 2][1] = ' ';
    this->_map[this->_width - 3][1] = ' ';
    this->_map[this->_width - 2][2] = ' ';

    this->_map[this->_width - 2][this->_length - 2] = ' ';
    this->_map[this->_width - 3][this->_length - 2] = ' ';
    this->_map[this->_width - 2][this->_length - 3] = ' ';
}

/**
 * @brief get all the map elements position
 *
 */
void MapGenerator::getElemPos()
{
    irr::core::vector3df pos;

    for (size_t x = 0; x != _map.size(); x++) {
        for (size_t y = 0; y != _map[x].size(); y++) {
            pos.X = x * 2;
            pos.Y = 0;
            pos.Z = y * 1.55;
            if (this->_map[x][y] == '#')
                this->_indestructibleBlocksPos.push_back(pos);
            else if (this->_map[x][y] == '0')
                this->_destructibleBlocksPos.push_back(pos);
            else if (this->_map[x][y] == '1')
                this->_PowerUpBlocksPos.push_back(pos);
        }
    }
}

/**
 * @brief Create a txt file for map preview
 *
 */
void MapGenerator::writeInfile()
{
    std::ofstream myfile;
    myfile.open(_name, std::ofstream::trunc);

    for (auto it = this->_map.begin(); it != this->_map.end(); ++it) {
        for (auto elemIterator = it->begin(); elemIterator != it->end(); ++elemIterator) {
            myfile << *elemIterator;
        }
            myfile << std::endl;
    }
    myfile.close();
}

/**
 * @brief getter for map's elements
 *
 * @param type
 * @return const std::vector<irr::core::vector3d<float>>
 */
const std::vector<irr::core::vector3d<float>> &MapGenerator::getElemVector3d(elemType type) const
{
    if (type == INDESTRUCTIBLE)
        return (this->_indestructibleBlocksPos);
    else if (type == DESTRUCTIBLE)
        return (this->_destructibleBlocksPos);
    else
        return (this->_PowerUpBlocksPos);
}

/**
 * @brief get the map length and width
 * 
 * @return std::queue<unsigned int> 
 */
const std::queue<unsigned int> MapGenerator::getMapDimension() const
{
    std::queue<unsigned int> dimension;

    dimension.push(this->_length);
    dimension.push(this->_width);
    return (dimension);

}

void MapGenerator::mapTxtToVector(std::string path)
{
    std::ifstream file(path);
    std::ostringstream fileContent;
    size_t pos = 0;

    this->_map.clear();
    this->_destructibleBlocksPos.clear();
    this->_indestructibleBlocksPos.clear();
    this->_PowerUpBlocksPos.clear();
    fileContent << file.rdbuf();
    file.close();
    getElemPosVector(fileContent.str());
}

void MapGenerator::setVector3dPos(size_t x, size_t y, std::string elem)
{
    irr::core::vector3d<float> pos;

    pos.X = x * 2;
    pos.Y = 0;
    pos.Z = y * 1.55;
    if (elem == "#")
        this->_indestructibleBlocksPos.push_back(pos);
    else if (elem == "0")
        this->_destructibleBlocksPos.push_back(pos);
    else if (elem == "1")
        this->_PowerUpBlocksPos.push_back(pos);
}

void MapGenerator::getElemPosVector(std::string fileContent)
{
    std::vector<irr::core::vector3d<float>> vectPos;
    size_t x = 0;
    size_t y = 0;

    for (size_t i = 0; i <= fileContent.size() - 1; i++) {
        if (fileContent.substr(i, 1) == "\n") {
            x += 1;
            y = 0;
        }
        else {
            setVector3dPos(x, y, fileContent.substr(i, 1));
            y += 1;
        }
    }
}
