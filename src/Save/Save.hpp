/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Save
*/

#ifndef SAVE_HPP_
#define SAVE_HPP_

#include "AppContext.hpp"
#include "GameException.hpp"

class Save {
	public:
		Save(AppContext *context);
		~Save();

    // Read all Files and Write all configs to files
    void readAllFiles();
    void downloadAllConfigs();

    private:
    // Read Keybiding File
    void saveKeyLine(std::string line, PlayerBind &);
    void saveKey(EKEY_CODE &up, std::string &line);
    int verifKeyFile(std::fstream &key);
    void readKeyFile();
    // Write Keybiding File
    void writeEachPlayerKeys(PlayerBind);
    void writeKeyFile();
    // Sound
    int verifSoundFile(int save);
    void readSoundFile();
    void writeSoundFile();
    // Character Selection
    void readPlayerFile();
    void writePlayerFile();
	std::fstream _open;             // Read keybinding file
    std::ofstream _write;           // Write keybiding file
    AppContext *_context;           // Communicate with whole game
};

#endif /* !SAVE_HPP_ */
