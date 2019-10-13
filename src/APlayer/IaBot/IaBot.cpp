/*
** EPITECH PROJECT, 2019
** IaBot.hpp
** File description:
** IA for the bot
*/

#include "IaBot.hpp"

IaBot::IaBot(level lvl, PlayerColor color, scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node) : APlayer()
{
    _lvlBot = lvl;
    int fillHistory = 0;

    while (fillHistory != lvl) {
        _historyMvt.push_back(movement::NOT_KNOWN);
        ++fillHistory;
    }
    _scenemgr = scenemgr;
    _vidriver = vidriver;
    _node = node;
    this->initWithColor(color);
    _model = _scenemgr->getMesh("./models/link/link.b3d");
    _link = _scenemgr->addAnimatedMeshSceneNode(_model, _node);
    _link->setMaterialTexture(0, _skin);
    _link->setMaterialFlag(video::EMF_LIGHTING, false);
    _collide = CollisionSystem();
    _action = Action::MOVE;
    _posBot.first = _link->getPosition().X;
    _posBot.second = _link->getPosition().Z;
}

IaBot::~IaBot()
{}

void IaBot::destroy()
{
    _link->remove();
}

void IaBot::setStartPos(const core::vector3df &pos)
{
    _posMov = pos;
    _link->setPosition(_posMov);
}

void IaBot::initWithColor(PlayerColor color)
{
    switch (color) {
        case RED:
            _skin = _vidriver->getTexture("./models/link/red.png");
            break;
        case BLUE:
            _skin = _vidriver->getTexture("./models/link/blue.png");
            break;
        case GREEN:
            _skin = _vidriver->getTexture("./models/link/green.png");
            break;
        case PURPLE:
            _skin = _vidriver->getTexture("./models/link/purple.png");
            break;
        default:
            break;
    }
}

void IaBot::moveAnimated(core::vector3df &dest)
{
    if (_posMov != dest) {
        _run = true;
        _posMov = dest;
        _link->setPosition(_posMov);
    } else {
        _run = false;
    }
    if (_run == true && _anim == false) {
        _link->setFrameLoop(11, 32);
        _anim = true;
    } else if (_run == false) {
        _link->setFrameLoop(0, 10);
        _anim = false;
    }
}

Action IaBot::action(std::vector<std::string> &map, ITimer *timer, std::vector<irr::core::vector3df> &player)
{
    _player = player;
    _posBot.first = _link->getPosition().X;
    _posBot.second = _link->getPosition().Z;

    findClosestPlayer();
    if (canIHide() == true && (destroyPlayer(timer) == true || destroyElem(timer, map) == true)) {
        hide();
    } else {
        moveToTheClosestPlayer(map, timer);
    }
    return _action;
}

Action IaBot::action(EventReceiver &event, std::vector<std::string> &map, ITimer *timer)
{
    return MOVE;
}

TypePlayer IaBot::getTypePlayer() const
{
    return TypePlayer::BOT_TYPE;
}

scene::ISceneNode *IaBot::getNode() const
{
    return _node;
}

scene::ISceneNode *IaBot::getModel() const
{
    return _link;
}

const core::vector3df &IaBot::getPosition() const
{
    return _posMov;
}

u32 IaBot::getRange() const
{
    return _range;
}

const bool IaBot::canIHide() const
{
    for (auto it_historyMvt = _historyMvt.begin(); it_historyMvt != _historyMvt.end(); ++it_historyMvt) {
        if (*it_historyMvt == movement::NOT_KNOWN) {
            return false;
        }
    }
    return true;
}

const bool IaBot::destroyPlayer(ITimer *timer)
{
    int distanceX = abs(_posBot.first - _posClosestPlayer.first);
    int distanceY = abs(_posBot.second - _posClosestPlayer.second);

    if (distanceX + distanceY <= 3) {
        _action = Action::PUT_BOMB;
	return true;
    }
    return false;
}

const bool IaBot::destroyElem(ITimer *timer, std::vector<std::string> &map)
{
    elemType nextUp = checkElemType(_posBot.first, _posBot.second + 1, map);
    elemType nextDown = checkElemType(_posBot.first, _posBot.second - 1, map);
    elemType nextRight = checkElemType(_posBot.first + 1, _posBot.second, map);
    elemType nextLeft = checkElemType(_posBot.first - 1, _posBot.second, map);

    if (nextUp == elemType::DESTRUCTIBLE
        || nextDown == elemType::DESTRUCTIBLE
        || nextRight == elemType::DESTRUCTIBLE
        || nextLeft == elemType::DESTRUCTIBLE) {
        _action = Action::PUT_BOMB;
	    return true;
        }
    return false;
}

const bool IaBot::destroyAnimated(ITimer *timer)
{
    static int last = 0;

    if (timer->getTime() - last > 300) {
        last = timer->getTime();
        _action = Action::PUT_BOMB;
       return true;
    }
    return false;
}

void IaBot::hide()
{
    core::vector3df dest = _posMov;

    for (auto itHistoryMvt = _historyMvt.begin(); itHistoryMvt != _historyMvt.end(); ++itHistoryMvt) {
        switch(*itHistoryMvt) {
            case movement::UP:
                dest.Z += 0.0775 + _acc;
                _link->setRotation(core::vector3df(0, 180, 0));
                this->moveAnimated(dest);
                break;
            case movement::DOWN:
                dest.Z -= 0.0775 + _acc;
                _link->setRotation(core::vector3df(0, 0, 0));
                this->moveAnimated(dest);
                break;
            case movement::LEFT:
                dest.X -= 0.1 + _acc;
                _link->setRotation(core::vector3df(0, 90, 0));
                this->moveAnimated(dest);
                break;
            case movement::RIGHT:
                dest.X += 0.1 + _acc;
                _link->setRotation(core::vector3df(0, -90, 0));
                this->moveAnimated(dest);
                break;
            default:
                break;
        }
    }
}

elemType IaBot::checkElemType(int x, int y, std::vector<std::string> &map)
{
    core::vector3df dest = _posMov;

    if (_collide.collide_Z(_link, map, -0.0775 + _acc) && _collide.destroyable_X(_link, map, -0.0775 + _acc) == true) {
        return elemType::DESTRUCTIBLE;
    } else if (_collide.collide_Z(_link, map, 0.0775 + _acc) && _collide.destroyable_X(_link, map, 0.0775 + _acc) == true) {
        return elemType::DESTRUCTIBLE;
    } else if (_collide.collide_X(_link, map, 0.1 + _acc) && _collide.destroyable_Z(_link, map, 0.1 + _acc) == true) {
        return elemType::DESTRUCTIBLE;
    } else if (_collide.collide_X(_link, map, -0.1 + _acc) && _collide.destroyable_Z(_link, map, -0.1 + _acc) == true) {
        return elemType::DESTRUCTIBLE;
    }
    return elemType::UNKNOWN;
}

void IaBot::findClosestPlayer()
{
    int idx = 0;
    float distance = 10000000;
    float distanceX = 0;
    float distanceY = 0;
    
    for (auto itPlayer = _player.begin(); itPlayer != _player.end(); itPlayer++) {
        if (itPlayer->X == _posBot.first && itPlayer->Z == _posBot.second) {
            continue;
        }
        distanceX = abs(_posBot.first - itPlayer->X);
        distanceY = abs(_posBot.second - itPlayer->Z);
        if (distanceX + distanceY <= distance) {
            distance = distanceX + distanceY;
            _posClosestPlayer.first = itPlayer->X;
            _posClosestPlayer.second = itPlayer->Z;
        }
        ++idx;
    }
    return;
}

void IaBot::moveToTheClosestPlayer(std::vector<std::string> &map, ITimer *timer) {
    int distanceX = abs(_posBot.first - _posClosestPlayer.first);
    int distanceY = abs(_posBot.second - _posClosestPlayer.second);
    core::vector3df dest = _posMov;
    int iterator = -1;
    static int last = 0;

    /*
    if (_lvlBot == level::EASY && distanceX + distanceY > 10) {
        return;
    }
    */
    if (distanceX >= distanceY) {
        if (_posBot.first - _posClosestPlayer.first > 0 
        && _collide.collide_Z(_link, map, 0.1)) {
            dest.X += 0.1 + _acc;
            _link->setRotation(core::vector3df(0, -90, 0));
            addToHistoryMvt(movement::LEFT);
            }
        } else if (_posBot.first - _posClosestPlayer.first < 0
        && _collide.collide_Z(_link, map, -0.1)) {
            dest.X -= 0.1 + _acc;
            _link->setRotation(core::vector3df(0, 90, 0));
            addToHistoryMvt(movement::RIGHT);
    }
    if (distanceX < distanceY) {
        if (_posBot.second - _posClosestPlayer.second > 0
        && _collide.collide_X(_link, map, 0.0775)) {
            dest.Z -= 0.0775 + _acc;
            _link->setRotation(core::vector3df(0, 0, 0));
            addToHistoryMvt(movement::UP);
        } else if (_posBot.second - _posClosestPlayer.second < 0
        && _collide.collide_X(_link, map, -0.0775)) {
            dest.Z += 0.0775 + _acc;
            _link->setRotation(core::vector3df(0, 180, 0));
            addToHistoryMvt(movement::DOWN);
        }
    }
    this->moveAnimated(dest);
}

void IaBot::addToHistoryMvt(movement mvt)
{
    for (auto it = _historyMvt.begin(); it != _historyMvt.end(); ++it) {
        if (mvt == movement::NOT_KNOWN)
            *it = mvt;
            return;
    }
    _historyMvt.erase(_historyMvt.begin());
    _historyMvt.push_back(mvt);
}

/* 
std::vector<irr::core::vector3df> &IaBot::convertMapToGrille(std::vector<irr::core::vector3df> &vector)
{
    for (auto itVector = vector.begin(); itVector != vector.end(); ++itVector) {
        itVector->X *= 1 / 2;
        itVector->Z *= 1 / 1.55;
    }
    return vector;
}
*/
