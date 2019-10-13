/*
** EPITECH PROJECT, 2019
** APlayer.cpp
** File description:
** APlayer abstract class implementation
*/

#include "APlayer.hpp"

APlayer::APlayer()
{
}

void APlayer::lessBombSlot()
{
    if (_maxStock > 2)
	_maxStock -= 1;
}

void APlayer::addBombSlot()
{
    _maxStock += 1;
}

void APlayer::addRange()
{
    _range += 1;
}

void APlayer::lessRange()
{
    if (_range > 1)
	_range -= 1;
}

void APlayer::addMaxRange()
{
    // todo: set a max range
    _range = 50;
}

void APlayer::addSpeed()
{
    _acc += 0.05f;
}

void APlayer::lessSpeed()
{
    _acc -= 0.05f;
}
