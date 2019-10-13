/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** Game class implementation
*/

#include "Game.hpp"

Game::Game(AppContext *context) : _manager(context)
{
    _context = context;
    _node = _context->scenemgr->addEmptySceneNode();
    _stock_map.init(_context->vidriver, _context->scenemgr);
}

Game::~Game()
{
}

void Game::initPlayers()
{
    _manager.addPlayer(GREEN, _context->player_green, _node, _p1pos);
    _manager.addPlayer(RED, _context->player_red, _node, _p2pos);
    _manager.addPlayer(PURPLE, _context->player_purple, _node, _p3pos);
    _manager.addPlayer(BLUE, _context->player_blue, _node, _p4pos);
}

void Game::initCamera()
{
    switch (_map->getMapSize()) {
    case SMALL:
	_context->scenemgr->addCameraSceneNode(_node, core::vector3df(9,20,18), core::vector3df(9,0,10));
	_p1pos = core::vector3df(14, 0, 1.55);
	_p2pos = core::vector3df(2, 0, 1.55);
	_p3pos = core::vector3df(14, 0, 13.95);
	_p4pos = core::vector3df(2, 0, 13.95);
	break;
    case MEDIUM:
	_context->scenemgr->addCameraSceneNode(_node, core::vector3df(12,25,20), core::vector3df(12,0,12));
	_p1pos = core::vector3df(22, 0, 1.55);
	_p2pos = core::vector3df(2, 0, 1.55);
	_p3pos = core::vector3df(22, 0, 20.15);
	_p4pos = core::vector3df(2, 0, 20.15);
	break;
    case LARGE:
	_context->scenemgr->addCameraSceneNode(_node, core::vector3df(15,30,24), core::vector3df(15,0,15));
	_p1pos = core::vector3df(30, 0, 1.55);
	_p2pos = core::vector3df(2, 0, 1.55);
	_p3pos = core::vector3df(30, 0, 26.35);
	_p4pos = core::vector3df(2, 0, 26.35);
	break;
    }
}

void Game::draw()
{
    _map = _stock_map.getMap(_context->map);
    this->initCamera();
    _map->create();
    _manager.setMap(_map->getMap(), _map->getModels(), _map);
    this->initPlayers();
}

void Game::destroy()
{
    _node->removeAll();
    _map->destroy();
    _map = nullptr;
    _manager.clear();
}

void Game::event(EventReceiver &receiver, ITimer *timer, SceneID &shown)
{
    if (receiver.isKeyDown(irr::KEY_ESCAPE)) {
	shown = MENU_SCENE;
    }
    _manager.manage(receiver, timer, shown);
}
