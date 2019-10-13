/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MusicManager
*/

/**
 * @file MusicManager.hpp
 * @author Thomas Lesueur (thomas.lesueur@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2019-06-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef MUSICMANAGER_HPP_
#define MUSICMANAGER_HPP_

#include <SFML/Audio.hpp>
#include <vector>

/**
 * @brief MusicManager Class
 * 
 */
class MusicManager {
	public:
		MusicManager();
		~MusicManager();

        void playMusic();
        void stopMusic();
        void setMusic(std::string path);
        void chooseBattleMusic();

	private:
        sf::Music _music;
        bool _isPlayed;
        bool _isLoaded;
};

#endif /* !MUSICMANAGER_HPP_ */
