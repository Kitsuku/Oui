/*
** EPITECH PROJECT, 2018
** player.cpp
** File description:
** player class methods
*/

#include "Player.hpp"
#include "Graphics.hpp"

Player::Player(int numberPlayer, Positions pos,
	std::vector<std::string> wanted_sprites,
	std::string bomb_live_sprite, std::string bomb_death_sprite) :
	ACharacter(numberPlayer, pos, wanted_sprites,
		bomb_live_sprite, bomb_death_sprite)
{
}

void	Player::defineUpDownAction(const irr::SEvent::SJoystickEvent &keys,
	std::vector<AObject *> objects)
{
	if (keys.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] < -10000) {
		this->_action = Action::UP;
		this->doAction(objects);
	} else if (keys.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] >
		10000) {
		this->_action = Action::DOWN;
		this->doAction(objects);
	}
}

void	Player::defineLeftRightAction(const irr::SEvent::SJoystickEvent &keys,
	std::vector<AObject *> objects)
{
	if (keys.Axis[irr::SEvent::SJoystickEvent::AXIS_X] < 10000) {
		this->_action = Action::LEFT;
		this->doAction(objects);
	}  else if (keys.Axis[irr::SEvent::SJoystickEvent::AXIS_X] >
		10000) {
		this->_action = Action::RIGHT;
		this->doAction(objects);
	}
}

void	Player::defineAction(const irr::SEvent::SJoystickEvent &keys,
	std::vector<AObject *> objects)
{
	defineUpDownAction(keys, objects);
	defineLeftRightAction(keys, objects);
	if (keys.IsButtonPressed(0)) {
		this->_action = Action::PUTBOMB;
		this->doAction(objects);
	}
}
