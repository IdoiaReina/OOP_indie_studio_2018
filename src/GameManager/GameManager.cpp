/*
** EPITECH PROJECT, 2019
** GameManager.cpp
** File description:
** GameManager class implementation
*/

#include "GameManager.hpp"

GameManager::GameManager(AppContext *context)
{
    srand(time(NULL));
    _context = context;
    _scenemgr = _context->scenemgr;
    _vidriver = _context->vidriver;
}

GameManager::~GameManager()
{
    this->clear();
}

void GameManager::clear()
{
    _mapModel.clear();
    _mapText.clear();
    _players.clear();
    auto bonus = _bonuses.begin();
    while (bonus != _bonuses.end()) {
        (*bonus)->destroy();
        ++bonus;
    }
    _bonuses.clear();
    _bombs.clear();
    _links.clear();
    _map = nullptr;
    _linkPos.clear();
    _linksState.clear();
}

void GameManager::setMap(std::vector<std::string> &mapText, std::vector<scene::ISceneNode *> &mapModel, std::shared_ptr<IMap> &map)
{
    _mapText = mapText;
    _mapModel = mapModel;
    _map = map;
}

void GameManager::addPlayer(PlayerColor color, PlayerState type, scene::ISceneNode *node, core::vector3df &pos)
{
    static u32 trick = 0;
    if (type <= 3) {
        std::unique_ptr<Player> player(std::make_unique<Player>(color,_scenemgr,_vidriver, node));
        switch (type) {
        case PLAYER_1:
            player->setControl(_context->player1._up, _context->player1._down, _context->player1._left, _context->player1._right, _context->player1._action);
            break;
        case PLAYER_2:
            player->setControl(_context->player2._up, _context->player2._down, _context->player2._left, _context->player2._right, _context->player2._action);
            break;
        case PLAYER_3:
            player->setControl(_context->player3._up, _context->player3._down, _context->player3._left, _context->player3._right, _context->player3._action);
            break;
        case PLAYER_4:
            player->setControl(_context->player4._up, _context->player4._down, _context->player4._left, _context->player4._right, _context->player4._action);
            break;
        }
        _players.push_back(std::move(player));
        player.release();
        player = nullptr;
    } else if (type == BOT) {
        level lvl = (trick % 2 == 0 ? EASY : HARD);
        _players.push_back(std::make_unique<IaBot>(lvl, color,_scenemgr,_vidriver, node));
    }
    if (type != DISABLED) {
        _links.push_back(_players.back()->getModel());
        _linksState.push_back(type);
    }
    _players.back()->setStartPos(pos);
}

void GameManager::addBomb(scene::ISceneNode *node, int range, const core::vector3df &pos, ITimer *timer)
{
    _bombs.push_back(Bomb(_scenemgr, _vidriver, node, range, pos, timer));
}

void GameManager::addBonus(core::vector3df &pos)
{
    u32 random = std::rand() % 100;
    if (random <= 10) { // FULLFIRE
        _bonuses.push_back(std::make_unique<FullFire>(_scenemgr, _vidriver, nullptr, pos));
    } else if (random > 10 && random <= 20) { // BombSlotDown
        _bonuses.push_back(std::make_unique<BombSlotDown>(_scenemgr, _vidriver, nullptr, pos));
    } else if (random > 20 && random <= 40) { // BombSlotUp
        _bonuses.push_back(std::make_unique<BombSlotUp>(_scenemgr, _vidriver, nullptr, pos));
    } else if (random > 40 && random <= 50) { // FireDown
        _bonuses.push_back(std::make_unique<FireDown>(_scenemgr, _vidriver, nullptr, pos));
    } else if (random > 50 && random <= 70) { // FireUp
        _bonuses.push_back(std::make_unique<FireUp>(_scenemgr, _vidriver, nullptr, pos));
    } else if (random > 70 && random <= 80) { // SpeedDown
        _bonuses.push_back(std::make_unique<SpeedDown>(_scenemgr, _vidriver, nullptr, pos));
    } else if (random > 80 && random <= 100) { // SpeedUp
        _bonuses.push_back(std::make_unique<SpeedUp>(_scenemgr, _vidriver, nullptr, pos));
    }
}

void GameManager::findAndDelete(ExplosionParticles &particule, elemType type)
{
    core::vector3df pos = particule.getPosition();
    core::vector3df posToDestroy;
    auto model_it = _mapModel.begin();

    while (model_it != _mapModel.end()) {
        if ((*model_it)->getID() == type && _col.collide(*model_it, pos) == true) {
            posToDestroy = (*model_it)->getPosition();
            _mapText[posToDestroy.Z / 1.55f][posToDestroy.X / 2.f] = ' ';
            (*model_it)->remove();
            model_it = _mapModel.erase(model_it);
            if (type == POWER_UP) {
                this->addBonus(posToDestroy);
            }
            continue;
        }
        ++model_it;
    }
}

void GameManager::killPlayer(ExplosionParticles &particule)
{
    auto player_it = _players.begin();
    auto state_it = _linksState.begin();;

    while (player_it != _players.end()) {
        if (_col.collide(particule.getBox(), particule.getPosition(), (*player_it)->getModel()) == true) {
            (*player_it)->destroy();
            player_it = _players.erase(player_it);
            state_it = _linksState.erase(state_it);
            continue;
        }
        ++player_it;
        ++state_it;
    }
}

void GameManager::destroyBonus(ExplosionParticles &particule)
{
    auto bonus_it = _bonuses.begin();

    while (bonus_it != _bonuses.end()) {
        if ((*bonus_it)->isDestructible() == true &&_col.collide(particule.getBox(), particule.getPosition(), (*bonus_it)->getModel()) == true) {
            (*bonus_it)->destroy();
            bonus_it = _bonuses.erase(bonus_it);
            continue;
        }
        ++bonus_it;
    }
}

void GameManager::explodeBomb(ExplosionParticles &particule)
{
    auto bomb_it = _bombs.begin();

    while (bomb_it != _bombs.end()) {
        if (_col.collide(particule.getBox(), particule.getPosition(), bomb_it->getModel()) == true) {
            bomb_it->forceBooming();
        }
        ++bomb_it;
    }
}

void GameManager::maybeKillOrDestroy(std::vector<Bomb>::iterator &bomb)
{
    std::vector<ExplosionParticles> explosion = bomb->getExplosionParticles();

    for (auto particule : explosion) {
        this->destroyBonus(particule);
        if (_col.collide(_mapModel, particule.getPosition(), DESTRUCTIBLE) == true) {
            this->findAndDelete(particule, DESTRUCTIBLE);
        } else if (_col.collide(_mapModel, particule.getPosition(), POWER_UP) == true) {
            this->findAndDelete(particule, POWER_UP);
        }
        this->killPlayer(particule);
        this->explodeBomb(particule);
    }
}

void GameManager::checkBomb()
{
    auto bomb = _bombs.begin();
    
    while (bomb != _bombs.end()) {
        bomb->explodeMaybe();
        if (bomb->isBooming()) {
            bomb->explode(_mapModel);
            this->maybeKillOrDestroy(bomb);
        } else if (bomb->isEnded()) {
            bomb = _bombs.erase(bomb);
            continue;
        }
        ++bomb;
    }
}

void GameManager::checkBonus(std::vector<std::unique_ptr<APlayer>>::iterator &player_it)
{
    auto bonus = _bonuses.begin();

    while (bonus != _bonuses.end()) {
        if (_col.collide((*bonus)->getModel(), (*player_it)->getModel()) == true) {
            (*bonus)->effect(*player_it);
            (*bonus)->destroy();
            bonus = _bonuses.erase(bonus);
            continue;
        }
        ++bonus;
    }
}

std::vector<core::vector3df> &GameManager::getLinksPos()
{
    auto player_it = _players.begin();

    _linkPos.clear();
    while (player_it != _players.end()) {
        _linkPos.push_back((*player_it)->getPosition());
        ++player_it;
    }
    return _linkPos;
}

void GameManager::manage(EventReceiver &receiver, ITimer *timer, SceneID &shown)
{
    auto player_it = _players.begin();

    if (_players.size() == 1) {
        _context->winner = _linksState.back();
        shown = END_GAME;
    }
    while (player_it != _players.end()) {
        if ((*player_it)->getTypePlayer() == PLAYER_TYPE) {
            if ((*player_it)->action(receiver, _mapText, timer) == PUT_BOMB) {
                this->addBomb((*player_it)->getNode(), (*player_it)->getRange(), (*player_it)->getPosition(), timer);
	    }
        } else {
            if ((*player_it)->action(_mapText, timer, this->getLinksPos()) == PUT_BOMB) {
                this->addBomb((*player_it)->getNode(), (*player_it)->getRange(), (*player_it)->getPosition(), timer);
            }
        }
        this->checkBonus(player_it);
        ++player_it;
    }
    this->checkBomb();
}
