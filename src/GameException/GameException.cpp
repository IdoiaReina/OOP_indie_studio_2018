/*
** EPITECH PROJECT, 2019
** GameException.cpp
** File description:
** GameException class implementation
*/

#include "GameException.hpp"

GameException::GameException(const std::string &msg) : _error(msg)
{
}

const char *GameException::what() const noexcept
{
    std::cout << "Game Exception : ";
    return _error.c_str();
}
