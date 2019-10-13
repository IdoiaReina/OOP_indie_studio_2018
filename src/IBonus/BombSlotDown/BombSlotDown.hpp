/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** BombSlotDown
*/

#ifndef BOMBSLOTDOWN_HPP_
#define BOMBSLOTDOWN_HPP_

#include "IBonus.hpp"
#include <memory>

class BombSlotDown : public IBonus {
	public:
	    BombSlotDown(scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node, core::vector3df &pos);
	    ~BombSlotDown() final;

        void effect(std::unique_ptr<APlayer> &) final;
        void destroy() final;
        scene::ISceneNode *getModel() const final;
        bool isDestructible() final;

	private:
        scene::ISceneNode *_node = nullptr;
        scene::ISceneManager *_scenemgr = nullptr;
        video::IVideoDriver *_vidriver = nullptr;
    
        video::ITexture *_skin = nullptr;
        scene::IAnimatedMesh *_model = nullptr;

        scene::IAnimatedMeshSceneNode *_mesh = nullptr;

        irr::core::vector3df _pos;

        std::chrono::high_resolution_clock::time_point _spawn;
        std::chrono::high_resolution_clock::time_point _stop;

        void create();
};

#endif /* !BOMBSLOTDOWN_HPP_ */
