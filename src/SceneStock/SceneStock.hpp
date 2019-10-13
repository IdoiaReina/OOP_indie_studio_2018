/*
** EPITECH PROJECT, 2019
** SceneStock.hpp
** File description:
** SceneStock class definition
*/

#ifndef SCENESTOCK_HPP_
#define SCENESTOCK_HPP_

#include <vector>
#include <memory>
#include <irrlicht.h>

#include "IScene.hpp"
#include "GameException.hpp"
#include "EventReceiver.hpp"
#include "AppContext.hpp"
#include "MusicManager.hpp"

/* All scenes */
#include "Menu.hpp"
#include "Settings.hpp"
#include "ChoosePlayer.hpp"
#include "MapSelector.hpp"
#include "Game.hpp"
#include "EndGame.hpp"
#include "SplashScreen.hpp"

using namespace irr;

class SceneStock
{
private:
    std::map<SceneID, std::unique_ptr<IScene>> _scene_stock;
    SceneID _shown = SPLASH_SCENE;

    MusicManager _musicManager;

    AppContext *_context;
public:
    SceneStock(AppContext *);
    SceneStock();
    ~SceneStock();

    void init(AppContext *);
    void change_scene(SceneID);
    void event_scene(EventReceiver &, ITimer *, SceneID &);
    void manageMusic(SceneID sceneIdx);
};

#endif
