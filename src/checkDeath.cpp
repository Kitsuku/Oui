/*
** EPITECH PROJECT, 2018
** checkDeath.cpp
** File description:
** checkDeath function
*/

#include <math.h>
#include <unistd.h>
#include <iostream>
#include "checkDeath.hpp"
#include "AObject.hpp"

bool	checkDeath::checkDieX(Positions object_pos, Positions bomb_pos,
		Bomb *bomb)
{
	int	power_left = bomb->getPower("left");
	int	power_right = bomb->getPower("right");
	Positions	pos;

	pos.x = floor(bomb_pos.x);
	pos.y = floor(bomb_pos.y);
	if (pos.y == object_pos.y &&
		((object_pos.x >= (pos.x - power_left)) &&
		(object_pos.x <= pos.x))) {
		return true;
	}
	pos.x = ceil(bomb_pos.x);
	pos.y = ceil(bomb_pos.y);
	if (pos.y == object_pos.y &&
		((object_pos.x <= (pos.x + power_right)) &&
		(object_pos.x >= pos.x))) {
		return true;
	}
	return false;
}

bool	checkDeath::checkDieY(Positions object_pos, Positions bomb_pos,
		Bomb *bomb)
{
	int	power_up = bomb->getPower("up");
	int	power_down = bomb->getPower("down");
	Positions	pos;

	pos.x = floor(bomb_pos.x);
	pos.y = floor(bomb_pos.y);
	if (pos.x == object_pos.x &&
		((object_pos.y >= (pos.y - power_up)) &&
		(object_pos.y <= pos.y))) {
		return true;
	}
	pos.x = ceil(bomb_pos.x);
	pos.y = ceil(bomb_pos.y);
	if (pos.x == object_pos.x &&
		((object_pos.y <= (pos.y + power_down)) &&
		(object_pos.y >= pos.y))) {
		return true;
	}
	return false;
}

bool    checkDeath::checkDie(Positions object_pos, Positions bomb_pos,
                Bomb *bomb)
{
	if (bomb == nullptr)
		return (false);
	object_pos.x = floor(object_pos.x);
	object_pos.y = floor(object_pos.y);
        if (checkDieX(object_pos, bomb_pos, bomb) == true)
                return true;
        if (checkDieY(object_pos, bomb_pos, bomb) == true)
                return true;
        return false;
}
