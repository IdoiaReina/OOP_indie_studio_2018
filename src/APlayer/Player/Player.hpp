/*
** EPITECH PROJECT, 2019
** Player.hpp
** File description:
** Player class definition
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <irrlicht.h>

#include "APlayer.hpp"
#include "AppContext.hpp"
#include "CollisionSystem.hpp"
#include "Bomb.hpp"

class Player : public APlayer
{
private:
    scene::ISceneNode *_node = nullptr;
    scene::ISceneManager *_scenemgr = nullptr;
    video::IVideoDriver *_vidriver = nullptr;

    video::ITexture *_skin = nullptr;
    scene::IAnimatedMesh *_model = nullptr;

    scene::IAnimatedMeshSceneNode *_link = nullptr;
    
    core::vector3df _pos;
    bool _run = false;
    bool _anim = false;
    u32 _bombOnGround = 0;
    CollisionSystem _collide;

    EKEY_CODE _up;
    EKEY_CODE _down;
    EKEY_CODE _left;
    EKEY_CODE _right;
    EKEY_CODE _bomb;

    void initWithColor(PlayerColor);
    void moveAnimated(core::vector3df &);
    bool bombEvent(EventReceiver &, ITimer *);
public:
    Player(PlayerColor, scene::ISceneManager *, video::IVideoDriver *, scene::ISceneNode *);
    ~Player() final;

    void setStartPos(const core::vector3df &) final;
    void setControl(EKEY_CODE, EKEY_CODE, EKEY_CODE, EKEY_CODE, EKEY_CODE);

    Action action(EventReceiver &, std::vector<std::string> &, ITimer *) final;
    Action action(std::vector<std::string> &, ITimer *, std::vector<core::vector3df> &) final;

    TypePlayer getTypePlayer() const final;
    scene::ISceneNode *getNode() const final;
    scene::ISceneNode *getModel() const final;
    const core::vector3df &getPosition() const final;
    u32 getRange() const final;
    void destroy() final;
};

#endif
