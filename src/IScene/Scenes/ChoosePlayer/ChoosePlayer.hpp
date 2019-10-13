/*
** EPITECH PROJECT, 2019
** Preparation.hpp
** File description:
** Preparation class definition
*/

#ifndef CHOOSEPLAYER_HPP_
#define CHOOSEPLAYER_HPP_

#include <irrlicht.h>
#include <vector>

#include "IScene.hpp"
#include "AppContext.hpp"
#include "MusicManager.hpp"

using namespace irr;

class ChoosePlayer : public IScene
{
    private:
        scene::ISceneNode *_node = nullptr;
        AppContext *_context;

        //Texture(s) :
        video::ITexture *_back = nullptr;
        video::ITexture *_arrow_up = nullptr;
        video::ITexture *_arrow_down = nullptr;
        video::ITexture *_arrow_up_pressed = nullptr;
        video::ITexture *_arrow_down_pressed = nullptr;

        //Image(s) :
        gui::IGUIImage *_mainImage = nullptr;

        //Variable(s) :
        int _where = 0;
        std::vector<int> _choice;
        std::vector<core::position2d<int>> _pos;
        std::vector<video::ITexture *> _status;
        bool pressed_up = false;
        bool pressed_down = false;
        bool keyboard_pressed = false;
        bool echap = false;
        bool _mouse = false;

        //Musics
        MusicManager _musicManager;
        

        //Méthode(s) :
        void _draw_arrow();
        void _status_arrow(int, EventReceiver &);
        void _arrow_move(EventReceiver &, ITimer *);
        void _draw_status();
        void _clear_display();
        void _file_vector();
        void _choose_correct();
        bool _found_in(int);
        void _mouse_click(EventReceiver &, ITimer *);
        void _check_arrow(irr::core::vector2di, ITimer *);
        bool _check_choice();
        void _reinit();

    public:
        //Construteur-Destruteurr :
        ChoosePlayer(AppContext *);
        ~ChoosePlayer() final;

        //Méthode(s) :
        void draw() final;
        void destroy() final;
        void event(EventReceiver &, ITimer *, SceneID &) final;
};

#endif
