/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** SoundManager
*/

#ifndef SOUNDMANAGER_HPP_
#define SOUNDMANAGER_HPP_

#include <SFML/Audio.hpp>

class SoundManager {
	public:
		SoundManager();
		~SoundManager();

        void playSound();
        void playSoundLoop();
        void stopSound();
        void setSound(std::string path);

	private:
        sf::Sound _sound;
        sf::SoundBuffer _buffer;
        bool _isPlayed;
        bool _isLoaded;
};

#endif /* !SOUNDMANAGER_HPP_ */
