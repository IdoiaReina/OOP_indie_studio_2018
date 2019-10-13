/*
** EPITECH PROJECT, 2019
** Preparation.hpp
** File description:
** Preparation class definition
*/

#ifndef ENDGAME_HPP_
#define ENDGAME_HPP_

#include <irrlicht.h>
#include <vector>

#include "IScene.hpp"
#include "AppContext.hpp"
#include "MusicManager.hpp"

using namespace irr;

class EndGame : public IScene
{
    private:
        scene::ISceneNode *_node = nullptr;
        AppContext *_context;

        //Texture(s) :
        video::ITexture *_back = nullptr;
        video::ITexture *_change_map = nullptr;
        video::ITexture *_change_player = nullptr;
        video::ITexture *_menu = nullptr;
        video::ITexture *_win = nullptr;

        //Image(s) :
        gui::IGUIImage *_mainImage = nullptr;
        PlayerState _winner = DISABLED;

        //Variable(s) :
        std::vector<core::position2d<int>> _pos;
        int button = 3;

        //Musics
        //MusicManager _musicManager;
        

        //Méthode(s) :
        void _draw_button();
        void _clear_display();
        void _file_vector();
        void _mouse_click(EventReceiver &, ITimer *);

    public:
        //Construteur-Destruteurr :
        EndGame(AppContext *);
        ~EndGame() final;

        //Méthode(s) :
        void draw() final;
        void destroy() final;
        void event(EventReceiver &, ITimer *, SceneID &) final;
};

#endif
