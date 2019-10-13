/*
** EPITECH PROJECT, 2019
** SplashScreen.hpp
** File description:
** SplashScreen scene definition
*/

#ifndef SPLASHSCREEN_HPP_
#define SPLASHSCREEN_HPP_

#include <irrlicht.h>

#include "IScene.hpp"
#include "AppContext.hpp"

class SplashScreen : public IScene
{
private:
    bool _drawn = false;

    video::ITexture *_back = nullptr;
    gui::IGUIImage *_guiBack = nullptr;

    video::ITexture *_head1 = nullptr;
    gui::IGUIImage *_guiHead1 = nullptr;

    video::ITexture *_head2 = nullptr;
    gui::IGUIImage *_guiHead2 = nullptr;

    video::ITexture *_head3 = nullptr;
    gui::IGUIImage *_guiHead3 = nullptr;

    video::ITexture *_head4 = nullptr;
    gui::IGUIImage *_guiHead4 = nullptr;

    video::ITexture *_head5 = nullptr;
    gui::IGUIImage *_guiHead5 = nullptr;

    video::ITexture *_head6 = nullptr;
    gui::IGUIImage *_guiHead6 = nullptr;

    gui::IGUIInOutFader *_fader = nullptr;

    u32 _start = 0;
    bool _first = false;
    bool _headOne = false;
    bool _headTwo = false;
    bool _headThree = false;
    bool _headFour = false;
    bool _headFive = false;
    bool _headSix = false;

    AppContext *_context;
public:
    SplashScreen(AppContext *);
    ~SplashScreen() final;

    void draw() final;
    void destroy() final;
    void event(EventReceiver &, ITimer *, SceneID &) final;
};

#endif
