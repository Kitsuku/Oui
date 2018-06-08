/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** method of the abstract class character
*/

#include "action.hpp"
#include "ACharacter.hpp"

ACharacter::ACharacter(int numberPlayer, Positions pos) :
	_nbrPlayer(numberPlayer)
{
	this->_position = pos;
	this->_nbrBomb = 1;
	this->_fireRange = 2;
	this->_speed = 0.1;
	this->_wallPass = false;
	this->_isDead = false;
}

ACharacter::~ACharacter()
{
}

void	ACharacter::doAction(Action action, std::vector<AObject *> objects)
{
	action = action;
	objects = objects;
}

void	ACharacter::putBomb(std::vector<AObject *> objects)
{
	objects = objects;
}
