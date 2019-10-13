/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MusicManager
*/

/**
 * @file MusicManager.cpp
 * @author Thomas Lesueur (thomas.lesueur@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2019-06-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "MusicManager.hpp"

/**
 * @brief Construct a new Music Manager:: Music Manager object
 * 
 */
MusicManager::MusicManager()
{
    srand(time(NULL));
    this->_isLoaded = false;
    this->_isPlayed = false;
}

/**
 * @brief Destroy the Music Manager:: Music Manager object
 * 
 */
MusicManager::~MusicManager()
{
}

/**
 * @brief play the loaded music
 * 
 */
void MusicManager::playMusic()
{
    if (this->_isLoaded == true) {
        this->_music.play();
        this->_isPlayed = true;
    }
}

/**
 * @brief stop the loaded music
 * 
 */
void MusicManager::stopMusic()
{
    if (this->_isLoaded == true && this->_isPlayed == true) {
        this->_music.stop();
        this->_isPlayed = false;
    }
}

/**
 * @brief set a music
 * 
 * @param path 
 */
void MusicManager::setMusic(std::string path)
{

    this->_music.openFromFile(path);
    this->_music.setLoop(1);
    this->_isLoaded = true;
}

/**
 * @brief Choose a battle music
 * 
 */
void MusicManager::chooseBattleMusic()
{
    int randomNb = rand() % 3;

    if (randomNb == 0)
        setMusic("./assets/musics/piste_1.ogg");
    else if (randomNb == 1)
        setMusic("./assets/musics/piste_2.ogg");
    else
        setMusic("./assets/musics/piste_3.ogg");


}