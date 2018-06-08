/*
** EPITECH PROJECT, 2018
** bombCheckHitWall.cpp
** File description:
** checkHitWall method from Bomb class
*/

#include <iostream>
#include "positions.hpp"
#include "classBomb.hpp"

void	Bomb::checkHitWall(Positions wall_pos)
{
	if (_position.y == wall_pos.y && (wall_pos.x >=
		(_position.x - _power_left)) && (wall_pos.x <= _position.x))
		_power_left = (_position.x - wall_pos.x);
	if (_position.y == wall_pos.y && (wall_pos.x <=
		(_position.x + _power_right)) && (wall_pos.x >= _position.x))
		_power_right = (wall_pos.x - _position.x);
	if (_position.x == wall_pos.x && (wall_pos.y >=
		(_position.y - _power_up)) && (wall_pos.y <= _position.y))
		_power_up = (_position.y - wall_pos.y);
	_power_down = (_position.x == wall_pos.x &&
		(wall_pos.y <= (_position.y + _power_down)) &&
		(wall_pos.y >= _position.y)) ?
			(wall_pos.y - _position.y) : (_power_down);
}
