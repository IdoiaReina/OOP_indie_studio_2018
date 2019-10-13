/*
** EPITECH PROJECT, 2019
** APlayer.hpp
** File description:
** Abstract class for playable entity
*/

#ifndef APLAYER_HPP_
#define APLAYER_HPP_

#include <irrlicht.h>

#include "EventReceiver.hpp"
#include <vector>

enum TypePlayer
{
    BOT_TYPE,
    PLAYER_TYPE
};

enum level
{
    EASY = 3,
    HARD = 5
};

enum Action
{
    PUT_BOMB = 0,
    MOVE,
};

class APlayer
{
protected:
    u32 _stock = 1;
    u32 _maxStock = 1;
    u32 _range = 1;
    f32 _acc = 0.05f;
public:
    APlayer();
    virtual ~APlayer() = default;

    virtual void destroy() = 0;
    virtual void setStartPos(const core::vector3df &) = 0;
    virtual TypePlayer getTypePlayer() const = 0;
    virtual scene::ISceneNode *getNode() const = 0;
    virtual scene::ISceneNode *getModel() const = 0;
    virtual const core::vector3df &getPosition() const = 0;
    virtual u32 getRange() const = 0;
    
    virtual Action action(EventReceiver &, std::vector<std::string> &, ITimer *) = 0;
    virtual Action action(std::vector<std::string> &, ITimer *, std::vector<core::vector3df> &) = 0;

    virtual void lessBombSlot();
    virtual void addBombSlot();
    virtual void addRange();
    virtual void lessRange();
    virtual void addMaxRange();
    virtual void addSpeed();
    virtual void lessSpeed();
};

#endif
