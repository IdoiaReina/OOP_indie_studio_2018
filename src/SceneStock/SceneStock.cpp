/*
** EPITECH PROJECT, 2019
** SceneStock.cpp
** File description:
** SceneStock class implémentation
*/

#include "SceneStock.hpp"
#include "Save.hpp"

SceneStock::SceneStock(AppContext *context)
{
    this->init(context);
}

SceneStock::SceneStock()
{
    // must come with a init() after
}

SceneStock::~SceneStock()
{
    _scene_stock.clear();
}

void SceneStock::init(AppContext *context)
{
    Save save(context);
    save.readAllFiles();
    _context = context;
    _scene_stock[SPLASH_SCENE] = std::make_unique<SplashScreen>(_context);
    _scene_stock[MENU_SCENE] = std::make_unique<Menu>(_context);
    _scene_stock[SETTINGS_SCENE] = std::make_unique<Settings>(_context);
    _scene_stock[CHOOSEPLAYER_SCENE] = std::make_unique<ChoosePlayer>(_context);
    _scene_stock[MAPSELECTOR_SCENE] = std::make_unique<MapSelector>(_context);
    _scene_stock[GAME_SCENE] = std::make_unique<Game>(_context);
    _scene_stock[END_GAME] = std::make_unique<EndGame>(_context);
    _scene_stock[SPLASH_SCENE]->draw();
    //manageMusic(MENU_SCENE);
    return;
}

void SceneStock::change_scene(SceneID scene_idx)
{
    if (scene_idx > _scene_stock.size())
        throw GameException("scene index too large");
    _scene_stock[_shown]->destroy();
    manageMusic(scene_idx);
    _scene_stock[scene_idx]->draw();
    _shown = scene_idx;

    Save save(_context);

    save.downloadAllConfigs();
    return;
}

void SceneStock::event_scene(EventReceiver &receiver, ITimer *timer, SceneID &shown)
{
    _scene_stock[_shown]->event(receiver, timer, shown);
}

 void SceneStock::manageMusic(SceneID sceneIdx)
{
    if (_context->music == false) {
        _musicManager.stopMusic();
    }
    if (!((sceneIdx == MAPSELECTOR_SCENE && _shown == CHOOSEPLAYER_SCENE) || (sceneIdx == CHOOSEPLAYER_SCENE && _shown == MAPSELECTOR_SCENE)))
        _musicManager.stopMusic();
    if ((sceneIdx == MAPSELECTOR_SCENE && _shown == CHOOSEPLAYER_SCENE) || (sceneIdx == CHOOSEPLAYER_SCENE && _shown == MAPSELECTOR_SCENE))
        return;
    if (sceneIdx == MENU_SCENE)
        _musicManager.setMusic("./assets/musics/menu.ogg");
    else if (sceneIdx == SETTINGS_SCENE || sceneIdx == CHOOSEPLAYER_SCENE || sceneIdx == MAPSELECTOR_SCENE)
        _musicManager.setMusic("./assets/musics/selection_perso.ogg");
    else
        _musicManager.chooseBattleMusic();
    if (_context->music == true)
        _musicManager.playMusic();
}
