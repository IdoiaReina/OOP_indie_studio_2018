/*
** EPITECH PROJECT, 2019
** Game.hpp
** File description:
** Game class definition
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <irrlicht.h>

#include "IScene.hpp"
#include "AppContext.hpp"
#include "MapStock.hpp"
#include "Player.hpp"
#include "GameManager.hpp"

using namespace irr;

class Game : public IScene
{
private:
    AppContext *_context;
    MapStock _stock_map;
    GameManager _manager;

    std::shared_ptr<IMap> _map = nullptr;

    scene::ISceneNode *_node = nullptr;

    core::vector3df _p1pos;
    core::vector3df _p2pos;
    core::vector3df _p3pos;
    core::vector3df _p4pos;

    void initPlayers();
    void initCamera();
public:
    Game(AppContext *);
    ~Game() final;

    void draw() final;
    void destroy() final;
    void event(EventReceiver &, ITimer *, SceneID &) final; 
};

#endif
