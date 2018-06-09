/*
** EPITECH PROJECT, 2018
** player.hpp
** File description:
** player class
*/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "AObject.hpp"
#include "Graphics.hpp"
#include "ACharacter.hpp"
#include "MyException.hpp"

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

class Player : public ACharacter
{
public:
	Player(int, Positions, std::vector<std::string>,
		std::string, std::string);
	Player();
	/* Methods */
	void	defineAction(const irr::SEvent::SJoystickEvent &,
			std::vector<AObject *>);
	void	defineUpDownAction(const irr::SEvent::SJoystickEvent &,
			std::vector<AObject *>);
	void	defineLeftRightAction(const irr::SEvent::SJoystickEvent &,
			std::vector<AObject *>);
};

#endif /* !PLAYER_HPP_ */
