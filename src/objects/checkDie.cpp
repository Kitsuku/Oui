/*
** EPITECH PROJECT, 2018
** checkDie.cpp
** File description:
** checks if you should die according to your position and a bomb position
*/

#include <memory>
#include <iostream>
#include "checkDie.hpp"

bool	checkDieX(Positions object_pos, Positions bomb_pos,
		Bomb *bomb)
{
	int	power_left = bomb->getPower("left");
	int	power_right = bomb->getPower("right");

	if (bomb_pos.y == object_pos.y &&
		(object_pos.x >= (bomb_pos.x - power_left)) &&
		(object_pos.x <= bomb_pos.x)) {
		return true;
	} else if (bomb_pos.y == object_pos.y &&
		(object_pos.x <= (bomb_pos.x + power_right)) &&
		(object_pos.x >= bomb_pos.x)) {
		return true;
	}
	return false;
}

bool	checkDieY(Positions object_pos, Positions bomb_pos,
		Bomb *bomb)
{
	int	power_up = bomb->getPower("up");
	int	power_down = bomb->getPower("down");

	if (bomb_pos.x == object_pos.x &&
		(object_pos.y >= (bomb_pos.y - power_up)) &&
		(object_pos.y <= bomb_pos.y)) {
		return true;
	} else if (bomb_pos.x == object_pos.x &&
		(object_pos.y <= (bomb_pos.y + power_down)) &&
		(object_pos.y >= bomb_pos.y)) {
		return true;
	}
	return false;
}

bool	checkDie(Positions object_pos, Positions bomb_pos,
		Bomb *bomb)
{
	if (checkDieX(object_pos, bomb_pos, bomb) == true)
		return true;
	if (checkDieY(object_pos, bomb_pos, bomb) == true)
		return true;
	return false;
}
