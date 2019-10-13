/*
** EPITECH PROJECT, 2019
** SplashScreen.cpp
** File description:
** SplashScreen scene implementation
*/

#include "SplashScreen.hpp"

SplashScreen::SplashScreen(AppContext *context)
{
    _context = context;
    _back = _context->vidriver->getTexture("./assets/back2.png");
    _head1 = _context->vidriver->getTexture("./assets/crew/idoia.png");
    _head2 = _context->vidriver->getTexture("./assets/crew/tony.png");
    _head3 = _context->vidriver->getTexture("./assets/crew/thomas.png");
    _head4 = _context->vidriver->getTexture("./assets/crew/paul.png");
    _head5 = _context->vidriver->getTexture("./assets/crew/joseph.png");
    _head6 = _context->vidriver->getTexture("./assets/crew/louis.png");
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::draw()
{
    _guiBack = _context->guienv->addImage(core::rect<s32>(0,0,1920,1080));
    _guiBack->setImage(_back);
    _guiBack->setScaleImage(true);
    _fader = _context->guienv->addInOutFader();
    _fader->setColor(video::SColor(0,0,0,0));
    _fader->fadeIn(1000);
}

void SplashScreen::destroy()
{
    _context->guienv->clear();
}

void SplashScreen::event(EventReceiver &receiver, ITimer *timer, SceneID &shown)
{
    if (_first == false) {
	_start = timer->getTime();
	_first = true;
    }
    if (timer->getTime() - _start > 1500 && _headOne == false) {
	_guiHead1 = _context->guienv->addImage(core::rect<s32>(400,350,550,550));
	_guiHead1->setImage(_head1);
	_guiHead1->setScaleImage(true);
	_headOne = true;
    } else if (timer->getTime() - _start > 2000 && _headTwo == false) {
	_guiHead2 = _context->guienv->addImage(core::rect<s32>(600,350,750,550));
	_guiHead2->setImage(_head2);
	_guiHead2->setScaleImage(true);
	_headTwo = true;
    } else if (timer->getTime() - _start > 2500 && _headThree == false) {
	_guiHead3 = _context->guienv->addImage(core::rect<s32>(800,350,950,550));
	_guiHead3->setImage(_head3);
	_guiHead3->setScaleImage(true);
	_headThree = true;
    } else if (timer->getTime() - _start > 3000 && _headFour == false) {
	_guiHead4 = _context->guienv->addImage(core::rect<s32>(1000,350,1150,550));
	_guiHead4->setImage(_head4);
	_guiHead4->setScaleImage(true);
	_headFour = true;
    } else if (timer->getTime() - _start > 3500 && _headFive == false) {
	_guiHead5 = _context->guienv->addImage(core::rect<s32>(1200,350,1350,550));
	_guiHead5->setImage(_head5);
	_guiHead5->setScaleImage(true);
	_headFive = true;
    } else if (timer->getTime() - _start > 4000 && _headSix == false) {
	_guiHead6 = _context->guienv->addImage(core::rect<s32>(1400,350,1550,550));
	_guiHead6->setImage(_head6);
	_guiHead6->setScaleImage(true);
	_headSix = true;
    } else if (timer->getTime() - _start > 4100) {
	shown = MENU_SCENE;
    }
}
