/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** SoundManager
*/

#include "SoundManager.hpp"

SoundManager::SoundManager()
{
    _isLoaded = false;
    _isPlayed = false;
}

SoundManager::~SoundManager()
{
}

void SoundManager::playSound()
{
    if (_isLoaded == true) {
        _sound.play();
        _isPlayed = true;
    }
}

void SoundManager::playSoundLoop()
{
    if (_isLoaded == true) {
        _sound.setLoop(1);
        _sound.play();
        _isPlayed = true;
    }
}

void SoundManager::stopSound()
{
    if (_isLoaded == true && _isPlayed == true) {
        _sound.stop();
        _isPlayed = false;
    }
}

void SoundManager::setSound(std::string path)
{
    _buffer.loadFromFile(path);
    _sound.setBuffer(_buffer);
    _isLoaded = true;
}