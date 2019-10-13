/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Save
*/

#include "Save.hpp"

Save::Save(AppContext *context) : _context(context)
{
}

Save::~Save()
{
}

/* Read Keybdinding File */

void Save::saveKey(EKEY_CODE &up, std::string &line)
{
    size_t pos = 0;
    std::string token;
    std::string delimiter = ";";

    pos = line.find(delimiter);
    token = line.substr(0, pos);
    for (size_t i = 0; i < token.length(); i++) {
        if (token[i] < '0' || token[i] > '9')
            throw GameException("Wrong Key in Config File.");
        }
    up = EKEY_CODE(std::stoi(token));
    line.erase(0, pos + delimiter.length());
}

void Save::saveKeyLine(std::string line, PlayerBind &p0)
{
    if (line.length() < 14)
        throw GameException("Wrong line in Keybinding Config File.");
    saveKey(p0._up, line);
    saveKey(p0._down, line);
    saveKey(p0._left, line);
    saveKey(p0._right, line);
    saveKey(p0._action, line);
}

int Save::verifKeyFile(std::fstream &key)
{
    std::string verif_line;
    size_t len = 0;

    while (std::getline(key, verif_line))
        len++;
    key.clear();
    key.seekg(0, key.beg);
    if (len != 4)
        throw GameException("Wrong Keybinding Config File.");
    return 0;
}

void Save::readKeyFile()
{
    std::string line;

    _open.open("src/Save/key.is");
    verifKeyFile(_open);
    std::getline(_open, line);
    saveKeyLine(line, _context->player1);
    std::getline(_open, line);
    saveKeyLine(line, _context->player2);
    std::getline(_open, line);
    saveKeyLine(line, _context->player3);
    std::getline(_open, line);
    saveKeyLine(line, _context->player4);
    _open.close();
}

/* Write/Save Keybiding File */

void Save::writeEachPlayerKeys(PlayerBind p0)
{
    _write << std::to_string(p0._up) << ";";
    _write << std::to_string(p0._down) << ";";
    _write << std::to_string(p0._left) << ";";
    _write << std::to_string(p0._right) << ";";
    _write << std::to_string(p0._action) << std::endl;
}

void Save::writeKeyFile()
{
    _write.open("src/Save/key.is", std::ofstream::trunc);
    writeEachPlayerKeys(_context->player1);
    writeEachPlayerKeys(_context->player2);
    writeEachPlayerKeys(_context->player3);
    writeEachPlayerKeys(_context->player4);
    _write.close();
}

/* Read sound file */

int Save::verifSoundFile(int save)
{
    std::string line;

    std::getline(_open, line);
    if (line.length() != 1)
        throw GameException("Wrong Sound Config File.");
    if (line[0] != '0' && line[0] != '1')
        throw GameException("Wrong Sound Config File : not a bool.");
    save = std::stoi(line);
    return (save);
}

void Save::readSoundFile()
{
    std::string line;
    size_t len = 0;

    _open.open("src/Save/sound.is");
    while (std::getline(_open, line))
        len++;
    _open.clear();
    _open.seekg(0, _open.beg);
    if (len != 2)
        throw GameException("Wrong Sound Config File.");
    _context->music = verifSoundFile(_context->music);
    _context->sound_effect = verifSoundFile(_context->sound_effect);
    _open.close();
}

/* Write Sound File */

void Save::writeSoundFile()
{
    _write.open("src/Save/sound.is", std::ofstream::trunc);
    _write << std::to_string(int(_context->music)) << std::endl;
    _write << std::to_string(int(_context->sound_effect)) << std::endl;
    _write.close();
}

/* Read Player File */

void Save::readPlayerFile()
{
    std::string line;
    size_t len = 0;

    _open.open("src/Save/player.is");
    while (std::getline(_open, line)) {
        len++;
        for (size_t i = 0; i < line.length(); i++) {
            if (line[i] < '0' || line[i] > '5')
                throw GameException("Wrong Player Config File.");
        }
    }
    if (len != 4)
        throw GameException("Wrong Player Config File.");
    _open.clear();
    _open.seekg(0, _open.beg);
    std::getline(_open, line);
    _context->player_green = PlayerState(std::stoi(line));
    std::getline(_open, line);
    _context->player_red = PlayerState(std::stoi(line));
    std::getline(_open, line);
    _context->player_purple = PlayerState(std::stoi(line));
    std::getline(_open, line);
    _context->player_blue = PlayerState(std::stoi(line));
    _open.close();
}

/* Write player File */

void Save::writePlayerFile()
{
    _write.open("src/Save/player.is", std::ofstream::trunc);
    _write << std::to_string(_context->player_green) << std::endl;
    _write << std::to_string(_context->player_red) << std::endl;
    _write << std::to_string(_context->player_purple) << std::endl;
    _write << std::to_string(_context->player_blue) << std::endl;
    _write.close();
}

/* ALL */

void Save::readAllFiles()
{
    readKeyFile();
    readSoundFile();
    readPlayerFile();
}

void Save::downloadAllConfigs()
{
    writeKeyFile();
    writeSoundFile();
    writePlayerFile();
}