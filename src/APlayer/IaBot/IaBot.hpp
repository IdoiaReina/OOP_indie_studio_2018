/*
** EPITECH PROJECT, 2019
** IaBot.hpp
** File description:
** IA for the bot
*/

#if !defined(IABOT_HPP_)
#define IABOT_HPP_

#include <irrlicht.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <utility>

#include "APlayer.hpp"
#include "AppContext.hpp"
#include "CollisionSystem.hpp"
#include "Bomb.hpp"
#include "MapGenerator.hpp"

enum movement
{ 
    UP,
    DOWN,
    RIGHT,
    LEFT,
    NOT_KNOWN
};

class IaBot : public APlayer
{
public:
    IaBot(level lvl, PlayerColor color, scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node);
    ~IaBot();

    void setStartPos(const core::vector3df &) final;

    Action action(std::vector<std::string> &map, ITimer *timer, std::vector<irr::core::vector3df> &player) final;
    Action action(EventReceiver &, std::vector<std::string> &, ITimer *) final;

    TypePlayer getTypePlayer() const final;
    scene::ISceneNode *getNode() const final;
    scene::ISceneNode *getModel() const final;
    const core::vector3df &getPosition() const final;
    u32 getRange() const final;
    void destroy() final;
private:   
    void initWithColor(PlayerColor color);
    void moveAnimated(core::vector3df &);
    void checkBomb();
    const bool canIHide() const;
    void addToHistoryMvt(movement mvt);
    const bool destroyPlayer(ITimer *timer);
    const bool destroyElem(ITimer *timer, std::vector<std::string> &map);
    const bool destroyAnimated(ITimer *timer);
    void hide();
    void findClosestPlayer();
    elemType checkElemType(int x, int y, std::vector<std::string> &map);
    void moveToTheClosestPlayer(std::vector<std::string> &map, ITimer *timer);
    std::vector<irr::core::vector3df> &convertMapToGrille(std::vector<irr::core::vector3df> &vector);
    
    scene::ISceneNode *_node = nullptr;
    scene::ISceneManager *_scenemgr = nullptr;
    video::IVideoDriver *_vidriver = nullptr;
    video::ITexture *_skin = nullptr;
    scene::IAnimatedMesh *_model = nullptr;
    scene::IAnimatedMeshSceneNode *_link = nullptr;
    std::vector<Bomb> _bombs;
    u32 _range = 1;
    core::vector3df _posMov;
    bool _run = false;
    bool _anim = false;
    CollisionSystem _collide;
    int _lvlBot;
    std::pair<float, float> _posBot;
    std::pair<float, float> _posClosestPlayer;
    std::vector<movement> _historyMvt;
    std::vector<irr::core::vector3df> _player;
    Action _action;
};

#endif // IABOT_HPP_
