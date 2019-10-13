/*
** EPITECH PROJECT, 2019
** Player.cpp
** File description:
** Player class implementation
*/

#include "Player.hpp"

Player::Player(PlayerColor color, scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node)
    : APlayer()
{
    _scenemgr = scenemgr;
    _vidriver = vidriver;
    _node = node;
    this->initWithColor(color);
    _model = _scenemgr->getMesh("./models/link/link.b3d");
    _link = _scenemgr->addAnimatedMeshSceneNode(_model, _node);
    _link->setMaterialTexture(0, _skin);
    _link->setMaterialFlag(video::EMF_LIGHTING, false);
    _collide = CollisionSystem();
}

Player::~Player()
{
}

void Player::destroy()
{
    _link->remove();
}

void Player::initWithColor(PlayerColor color)
{
    switch (color) {
    case RED:
        _skin = _vidriver->getTexture("./models/link/red.png");
        this->setControl(KEY_KEY_T, KEY_KEY_G, KEY_KEY_F, KEY_KEY_H, KEY_KEY_R);
        break;
    case BLUE:
        _skin = _vidriver->getTexture("./models/link/blue.png");
        this->setControl(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_PRIOR);
        break;
    case GREEN:
        _skin = _vidriver->getTexture("./models/link/green.png");
        this->setControl(KEY_KEY_Z, KEY_KEY_S, KEY_KEY_Q, KEY_KEY_D, KEY_KEY_A);
        break;
    case PURPLE:
        _skin = _vidriver->getTexture("./models/link/purple.png");
        this->setControl(KEY_KEY_I, KEY_KEY_K, KEY_KEY_J, KEY_KEY_L, KEY_KEY_U);
        break;
    }
}

void Player::setControl(EKEY_CODE up, EKEY_CODE down, EKEY_CODE left, EKEY_CODE right, EKEY_CODE bomb)
{
    _up = up;
    _down = down;
    _left = left;
    _right = right;
    _bomb = bomb;
}

void Player::setStartPos(const core::vector3df &pos)
{
    _pos = pos;
    _link->setPosition(_pos);
}

void Player::moveAnimated(core::vector3df &dest)
{
    if (_pos != dest) {
        _run = true;
        _pos = dest;
        _link->setPosition(_pos);
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

bool Player::bombEvent(EventReceiver &receiver, ITimer *timer)
{
    static u32 last = 0;
    static u32 refresh = 0;
    bool bomb_put = false;

    if (receiver.isKeyDown(_bomb) && _stock > 0 && (timer->getTime() - last) > 1000) {
        last = timer->getTime();
        --_stock;
	bomb_put = true;
    }
    if (_stock < _maxStock && (timer->getTime() - refresh) > 6000) {
	refresh = timer->getTime();
	++_stock;
    }
    return bomb_put;
}

Action Player::action(EventReceiver &receiver, std::vector<std::string> &map, ITimer *timer)
{
    core::vector3df dest = _pos;

    if (receiver.isKeyDown(_up) && _collide.collide_Z(_link, map, -0.0775 + _acc)) {
        dest.Z -= 0.0775 + _acc;
        _link->setRotation(core::vector3df(0, 0, 0));
    } else if (receiver.isKeyDown(_down) && _collide.collide_Z(_link, map, 0.0775 + _acc)) {
        dest.Z += 0.0775 + _acc;
        _link->setRotation(core::vector3df(0, 180, 0));
    } else if (receiver.isKeyDown(_left) && _collide.collide_X(_link, map, 0.1 + _acc)) {
        dest.X += 0.1 + _acc;
        _link->setRotation(core::vector3df(0, -90, 0));
    } else if (receiver.isKeyDown(_right) && _collide.collide_X(_link, map, -0.1 + _acc)) {
        dest.X -= 0.1 + _acc;
        _link->setRotation(core::vector3df(0, 90, 0));
    }
    this->moveAnimated(dest);
    if (this->bombEvent(receiver, timer) == true)
	return PUT_BOMB;
    else
	return MOVE;
}

Action Player::action(std::vector<std::string> &map, ITimer *timer, std::vector<core::vector3df> &player)
{
    return MOVE;
}

scene::ISceneNode *Player::getModel() const
{
    return _link;
}

TypePlayer Player::getTypePlayer() const
{
    return PLAYER_TYPE; 
}

scene::ISceneNode *Player::getNode() const
{
    return _node;
}

const core::vector3df &Player::getPosition() const
{
    return _pos;
}

u32 Player::getRange() const
{
    return _range;
}
