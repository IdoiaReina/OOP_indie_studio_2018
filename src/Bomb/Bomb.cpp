/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node, int range, const core::vector3df &pos, ITimer *timer)
{
    _node = node;
    _scenemgr = scenemgr;
    _vidriver = vidriver;
    _isPiercing = false;
    _range = range;
    _pos = pos;
    _skin = _vidriver->getTexture("./models/bomb/bomb.png");
    _model = _scenemgr->getMesh("./models/bomb/bomb.dae");
    _model->setHardwareMappingHint(scene::EHM_STATIC);
    _mesh = _scenemgr->addAnimatedMeshSceneNode(_model, _node);
    _mesh->setPosition(_pos);
    _mesh->setMaterialTexture(0, _skin);
    _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
    _timer = timer;
    _startTime = this->_timer->getTime();
}

Bomb::~Bomb()
{
}

const u32 Bomb::getElapsedTime()
{
    return (this->_timer->getTime() - this->_startTime);
}

scene::ISceneNode *Bomb::getModel() const
{
    return _mesh;
}

bool Bomb::isBooming()
{
    return _boom;
}

bool Bomb::isEnded()
{
    return (this->getElapsedTime() >= (compteARebour + 1000) && _boom == false ? true : false);
}

std::vector<ExplosionParticles> &Bomb::getExplosionParticles()
{
    return _explosion;
}

void Bomb::explodeNorth(std::vector<scene::ISceneNode *> &map)
{
    int range = 1;
    core::vector3df tmp = core::vector3df(_pos.X,_pos.Y,_pos.Z - (1.55 * range));

    while (range <= _range && _col.collide(map, tmp, INDESTRUCTIBLE) == false) {
	tmp = core::vector3df(_pos.X,_pos.Y,_pos.Z - (1.55 * range));
	_explosion.push_back(ExplosionParticles(_scenemgr, _vidriver, tmp, _node));
	++range;
    }
}

void Bomb::explodeSouth(std::vector<scene::ISceneNode *> &map)
{
    int range = 1;
    core::vector3df tmp = core::vector3df(_pos.X,_pos.Y,_pos.Z + (1.55 * range));

    while (range <= _range && _col.collide(map, tmp, INDESTRUCTIBLE) == false) {
	tmp = core::vector3df(_pos.X,_pos.Y,_pos.Z + (1.55 * range));
	_explosion.push_back(ExplosionParticles(_scenemgr, _vidriver, tmp, _node));
	++range;
    }
}

void Bomb::explodeEast(std::vector<scene::ISceneNode *> &map)
{
    int range = 1;
    core::vector3df tmp = core::vector3df(_pos.X - (2 * range),_pos.Y,_pos.Z);

    while (range <= _range && _col.collide(map, tmp, INDESTRUCTIBLE) == false) {
	tmp = core::vector3df(_pos.X - (2 * range),_pos.Y,_pos.Z);
	_explosion.push_back(ExplosionParticles(_scenemgr, _vidriver, tmp, _node));
	++range;
    }
}

void Bomb::explodeWest(std::vector<scene::ISceneNode *> &map)
{
    int range = 1;
    core::vector3df tmp = core::vector3df(_pos.X + (2 * range), _pos.Y, _pos.Z);

    while (range <= _range && _col.collide(map, tmp, INDESTRUCTIBLE) == false) {
	tmp = core::vector3df(_pos.X + (2 * range), _pos.Y, _pos.Z);
	_explosion.push_back(ExplosionParticles(_scenemgr, _vidriver, tmp, _node));
	++range;
    }
}

void Bomb::explode(std::vector<scene::ISceneNode *> &map)
{
    _explosion.push_back(ExplosionParticles(_scenemgr, _vidriver, _pos, _node));
    this->explodeNorth(map);
    this->explodeSouth(map);
    this->explodeEast(map);
    this->explodeWest(map);
}

void Bomb::forceBooming()
{
    if (_isPiercing == false) {
	compteARebour = 0;
	_startTime = _timer->getTime();
	_isPiercing = true;
    }
}

void Bomb::explodeMaybe()
{
    if (this->getElapsedTime() >= compteARebour && _boom == false) {
        _boom = true;
    }
    if (_boom == true && this->getElapsedTime() >= (compteARebour + 1000)) {
	for (auto particle : _explosion) {
	    particle.unBoom();
	}
	_explosion.clear();
	_mesh->remove();
	_boom = false;
    }
}

void Bomb::setPiercing(bool isPiercing)
{
    this->_isPiercing = isPiercing;
}
