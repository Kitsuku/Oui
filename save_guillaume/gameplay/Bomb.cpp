/*
** EPITECH PROJECT, 2018
** Bomb.cpp
** File description:
** Bomb methods
*/

#include "Bomb.hpp"
#include "checkDie.hpp"
#include "AObject.hpp"

Bomb::Bomb(int nbr_player, int given_power, Positions pos,
	std::string lifeSprite, std::string deathSprite)
{
	time(&(this->_time));
	this->_nbrPlayer = nbr_player;
	this->_power_default = given_power;
	this->_power_up = given_power;
	this->_power_down = given_power;
	this->_power_left = given_power;
	this->_power_right = given_power;
	this->_livingSprites = lifeSprite;
	this->_dyingSprites = deathSprite;
	this->_isDestroyed = false;
	this->_objectType = objectType::BOMB;
	this->_position = pos;
}

void	Bomb::checkTime()
{
	double	seconds;
	time_t	now;

	time(&now);
	seconds = difftime(now, this->_time);
	if (seconds >= 3)
		this->destroy();
}

void	Bomb::destroy()
{
	this->_isDestroyed = true;
}

int	Bomb::getPower(std::string asked)
{
	if (asked.compare("default") == 0)
		return this->_power_default;
	if (asked.compare("up") == 0)
		return this->_power_up;
	else if (asked.compare("down") == 0)
		return this->_power_down;
	else if (asked.compare("left") == 0)
		return this->_power_left;
	return this->_power_right;
}

void	Bomb::updatePower(AObject *object)
{
	if (object->getObjectType() == objectType::WALL ||
	object->getObjectType() == objectType::UNBRWALL) {
		checkHitWall(object->getPos());
	}
}

void	Bomb::updateTimer(AObject *object)
{
	Bomb	*bomb;

	if (object->getObjectType() == objectType::BOMB &&
	object->getIsDestroyed() == true) {
		bomb = (Bomb *)object;
		if (checkDie(_position, bomb->getPos(), bomb))
			this->destroy();
	}
}

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
