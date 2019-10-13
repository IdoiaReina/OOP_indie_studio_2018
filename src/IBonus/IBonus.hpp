/*
** EPITECH PROJECT, 2019
** IBonus.hpp
** File description:
** IBonus class definition
*/

#ifndef IBONUS_HPP_
#define IBONUS_HPP_

#include "APlayer.hpp"
#include <memory>
#include <chrono>

class IBonus
{
public:
    virtual ~IBonus() = default;

    virtual void effect(std::unique_ptr<APlayer> &) = 0;
    virtual void destroy() = 0;
    virtual scene::ISceneNode *getModel() const = 0;
    virtual bool isDestructible() = 0;
};

#endif
