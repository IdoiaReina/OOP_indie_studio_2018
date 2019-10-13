/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** SpeedUp
*/

#ifndef SPEEDUP_HPP_
#define SPEEDUP_HPP_

#include "IBonus.hpp"
#include <memory>

class SpeedUp : public IBonus {
	public:
	    SpeedUp(scene::ISceneManager *scenemgr, video::IVideoDriver *vidriver, scene::ISceneNode *node, core::vector3df &pos);
	    ~SpeedUp() final;

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

#endif /* !SPEEDUP_HPP_ */
