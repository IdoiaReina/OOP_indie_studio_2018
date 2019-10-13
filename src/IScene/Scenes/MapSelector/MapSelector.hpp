/*
** EPITECH PROJECT, 2019
** Preparation.hpp
** File description:
** Preparation class definition
*/

#ifndef MAPSELECTOR_HPP_
#define MAPSELECTOR_HPP_

#include <irrlicht.h>

#include "IScene.hpp"
#include "AppContext.hpp"
#include "MusicManager.hpp"

using namespace irr;

class MapSelector : public IScene
{
    private:
        scene::ISceneNode *_node = nullptr;
        AppContext *_context;

        //Texture(s) :
        video::ITexture *_back = nullptr;
        video::ITexture *_bordure_name = nullptr;
        video::ITexture *_cadre = nullptr;
        video::ITexture *_selected = nullptr;
        video::ITexture *_locked = nullptr;

        //Image(s) :
        gui::IGUIImage *_cadreI = nullptr;
        gui::IGUIImage *_backI = nullptr;
        gui::IGUIImage *_selectedI = nullptr;
        gui::IGUIImage *_lockedI = nullptr;
        gui::IGUIImage *_nameI = nullptr;

        //Variable(s) :
        int selected_x = 80;
        int selected_y = 325;
        int map_selected = 0;
        int col = 0;
        int line = 0;
        bool selected = false;
        int selected_lock = 0;
        bool enter = false;
        std::vector<video::ITexture *> _map;
        std::vector<video::ITexture *> _name;

        //Musics
        //MusicManager _musicManager;

        //Méthode(s) :
        void _draw_cadre();
        void reinit();
        void clear_display();
        void update_pos();
        void selected_map(EventReceiver &, ITimer *);
        void mouse_clic(EventReceiver &, ITimer *);
        void lock_enter(EventReceiver &, ITimer *);
        bool in_cadre(EventReceiver &, irr::core::vector2di);
        void _fill_vector(std::string, std::vector<video::ITexture *> &);
        void _print_map_vector();

    public:
        //Construteur-Destruteurr :
        MapSelector(AppContext *);
        ~MapSelector() final;

        //Méthode(s) :
        void draw() final;
        void destroy() final;
        void event(EventReceiver &, ITimer *, SceneID &) final;
};

#endif
