/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** SaveGame
*/

#ifndef SAVEGAME_HPP_
#define SAVEGAME_HPP_

#include "Save.hpp"

using namespace irr;
using namespace gui;

class SaveGame {
	public:
		SaveGame();
		~SaveGame();

    void loadFile(AppContext *context, std::string load_file) const;
    void loadButton(AppContext *context) const;
	protected:

    AppContext *_context;
	private:
};

#endif /* !SAVEGAME_HPP_ */
