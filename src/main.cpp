/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Indie's main
*/

#include "GameException.hpp"
#include "Indie.hpp"

int main(void)
{
    try {
	Indie studio;

	studio.letsgo();
    } catch (GameException &e) {
	std::cout << e.what() << std::endl;
	return 84;
    }
    return 0;
}
