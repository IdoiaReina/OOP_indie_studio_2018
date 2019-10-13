/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** FireUp
*/

#ifndef FIREUP_HPP_
#define FIREUP_HPP_

#include "IBonus.hpp"
#include <memory>

class FireUp : public IBonus {
	public:
		FireUp(scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node, core::vector3df &pos);
		~FireUp() final;

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

#endif /* !FIREUP_HPP_ */
