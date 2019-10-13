/*
** EPITECH PROJECT, 2019
** GameManager.hpp
** File description:
** GameManager class definition
*/

#ifndef GAMEMANAGER_HPP_
#define GAMEMANAGER_HPP_

#include <irrlicht.h>
#include <vector>

#include "AppContext.hpp"
#include "Bomb.hpp"
#include "EventReceiver.hpp"
#include "CollisionSystem.hpp"
#include "IScene.hpp"

/* Players */
#include "APlayer.hpp"
#include "Player.hpp"
#include "IaBot.hpp"

/* Bonuses */
#include "IBonus.hpp"
#include "BombSlotDown.hpp"
#include "BombSlotUp.hpp"
#include "FireDown.hpp"
#include "FireUp.hpp"
#include "SpeedUp.hpp"
#include "SpeedDown.hpp"
#include "FullFire.hpp"

using namespace irr;

class GameManager
{
private:
    AppContext *_context;
    CollisionSystem _col;
    scene::ISceneManager *_scenemgr = nullptr;
    video::IVideoDriver *_vidriver = nullptr;

    std::shared_ptr<IMap> _map = nullptr;
    std::vector<scene::ISceneNode *> _mapModel;
    std::vector<std::string> _mapText;
    std::vector<std::unique_ptr<APlayer>> _players;
    std::vector<scene::ISceneNode *> _links;
    std::vector<core::vector3df> _linkPos;
    std::vector<PlayerState> _linksState;
    std::vector<std::unique_ptr<IBonus>> _bonuses;
    std::vector<Bomb> _bombs;

    void findAndDelete(ExplosionParticles &, elemType);
    void maybeKillOrDestroy(std::vector<Bomb>::iterator &);
    void checkBomb();
    void checkBonus(std::vector<std::unique_ptr<APlayer>>::iterator &);
    void killPlayer(ExplosionParticles &);
    void destroyBonus(ExplosionParticles &);
    void explodeBomb(ExplosionParticles &);
    std::vector<core::vector3df> &getLinksPos();
public:
    GameManager(AppContext *);
    ~GameManager();

    void setMap(std::vector<std::string> &, std::vector<scene::ISceneNode *> &, std::shared_ptr<IMap> &);
    void addPlayer(PlayerColor, PlayerState, scene::ISceneNode *, core::vector3df &);
    void addBomb(scene::ISceneNode *, int, const core::vector3df &, ITimer *);
    void addBonus(core::vector3df &);
    void manage(EventReceiver &, ITimer *, SceneID &);
    void clear();
};

#endif
