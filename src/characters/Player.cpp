/*
** EPITECH PROJECT, 2018
** player.cpp
** File description:
** player class methods
*/

#include <irrlicht.h>
#include "driverChoice.h"
#include "Player.hpp"
#include "Graphics.hpp"

Player::Player(int numberPlayer, Positions pos,
	std::vector<std::string> wanted_sprites,
	std::string bomb_live_sprite, std::string bomb_death_sprite) :
	ACharacter(numberPlayer, pos, wanted_sprites,
		bomb_live_sprite, bomb_death_sprite)
{
}

Player::Player()
{
}

bool	Player::defineUpDownAction(const irr::SEvent::SJoystickEvent &keys,
	std::vector<AObject *> objects)
{
	bool	hasMoved = false;

	if (keys.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] < -10000) {
		this->_action = Action::UP;
		this->doAction(objects);
		hasMoved = true;
	} else if (keys.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] > 10000) {
		this->_action = Action::DOWN;
		this->doAction(objects);
		hasMoved = true;
	}
	return hasMoved;
}

bool	Player::defineLeftRightAction(const irr::SEvent::SJoystickEvent &keys,
	std::vector<AObject *> objects)
{
	bool	hasMoved = false;

	if (keys.Axis[irr::SEvent::SJoystickEvent::AXIS_X] < -10000) {
		this->_action = Action::LEFT;
		this->doAction(objects);
		hasMoved = true;
	}  else if (keys.Axis[irr::SEvent::SJoystickEvent::AXIS_X] > 10000) {
		this->_action = Action::RIGHT;
		this->doAction(objects);
		hasMoved = true;
	}
	return hasMoved;
}

AObject	*Player::defineAction(
	const irr::SEvent::SJoystickEvent &keys, std::vector<AObject *> objects)
{
	AObject	*bomb;
	bool	hasMoved = false;

	hasMoved = defineUpDownAction(keys, objects);
	if (hasMoved == false)
		hasMoved = defineLeftRightAction(keys, objects);
	if (keys.IsButtonPressed(1) && _nbrPutBomb < _nbrMaxBomb) {
		this->_action = Action::PUTBOMB;
		bomb = this->doAction(objects);
		return bomb;
	} else if (hasMoved == false){
		this->_action = Action::IDLE;
	}
	return nullptr;
}
