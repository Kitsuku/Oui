/*
** EPITECH PROJECT, 2018
** player.hpp
** File description:
** player class
*/

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <stdio.h>
#include <irrlicht.h>
#include "AObject.hpp"
#include "ACharacter.hpp"
#include "MyException.hpp"

class Player : public ACharacter
{
public:
	Player(int, Positions, std::vector<std::string>,
		std::string, std::string);
	Player();
	/* Methods */
	AObject	*defineAction(const irr::SEvent::SJoystickEvent &,
			std::vector<AObject *>);
	bool	defineUpDownAction(const irr::SEvent::SJoystickEvent &,
			std::vector<AObject *>);
	bool	defineLeftRightAction(const irr::SEvent::SJoystickEvent &,
			std::vector<AObject *>);
};

#endif /* !PLAYER_HPP_ */
