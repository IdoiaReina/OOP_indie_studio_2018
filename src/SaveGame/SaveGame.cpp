/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** SaveGame
*/

#include "SaveGame.hpp"

SaveGame::SaveGame()
{
}

SaveGame::~SaveGame()
{
}

void SaveGame::loadButton(AppContext *_context) const
{
    IGUIEnvironment* env = _context->guienv;
	env->addFileOpenDialog(L"Please choose a save file.", true, 0, -1, false);
}

void SaveGame::loadFile(AppContext *context, std::string load_path) const
{
}