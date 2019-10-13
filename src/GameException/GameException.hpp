/*
** EPITECH PROJECT, 2019
** GameException.hpp
** File description:
** GameException class definition
*/

#ifndef GAMEEXCEPTION_HPP_
#define GAMEEXCEPTION_HPP_

#include <exception>
#include <iostream>

class GameException : public std::exception
{
private:
    const std::string _error;
public:
    GameException(const std::string &);

    const char *what() const noexcept override;
};

#endif
