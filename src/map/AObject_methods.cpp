/*
** EPITECH PROJECT, 2018
** AObjects_methods.cpp
** File description:
** AObjects methods
*/

#include <iostream>
#include "checkDie.hpp"
#include "classBomb.hpp"
#include "classWall.hpp"
#include "classBonus.hpp"
#include "classUnbrWall.hpp"
#include "AObject.hpp"

objectType		AObject::getObjectType()
{
	return this->_objectType;
}

std::vector<int>	AObject::getLivingSprites()
{
	return this->_livingSprites;
}

std::vector<int>	AObject::getDyingSprites()
{
	return this->_dyingSprites;
}

Positions		AObject::getPos()
{
	return this->_position;
}

bool			AObject::getIsDestroyed()
{
	return this->_isDestroyed;
}

void	AObject::setObjectType(objectType type)
{
	this->_objectType = type;
}

void	AObject::setLivingSprites(std::vector<int> sprite)
{
	this->_livingSprites = sprite;
}

void	AObject::setDyingSprites(std::vector<int> sprite)
{
	this->_dyingSprites = sprite;
}

void	AObject::setPos(Positions pos)
{
	this->_position = pos;
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

Bomb::Bomb(int given_power, Positions pos,
	std::vector<int> lifeSprite, std::vector<int> deathSprite)
{
	time(&(this->_time));
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
	// appelle affichage
	std::cout << "BOMB destroying (call aff method)" << std::endl;
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

Wall::Wall(Positions pos, std::vector<int> lifeSprite,
	std::vector<int> deathSprite)
{
	this->_livingSprites = lifeSprite;
	this->_dyingSprites = deathSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::WALL;
}

void	Wall::checkBreak(AObject *object)
{
	Bomb	*bomb;

	if (object->getObjectType() == objectType::BOMB &&
	object->getIsDestroyed() == true) {
		bomb = (Bomb *)object;
		if (checkDie(_position, bomb->getPos(), bomb))
			this->destroy();
	}
}

void	Wall::destroy()
{
	// appelle affichage
	std::cout << "WALL destroying... (call aff method)" << std::endl;
	this->_isDestroyed = true;
}

int	getObjectAtPosition(float posX, float posY,
			std::vector<AObject *> objects)
{
	int		final_index = -1;
	int		count_index = 0;
	Positions	actual_object_pos;

	for (auto it = objects.begin(); it != objects.end(); it++) {
		actual_object_pos = (*it)->getPos();
		if (actual_object_pos.x == posX &&
		actual_object_pos.y == posY) {
			final_index = count_index;
		}
		count_index += 1;
	}
	return final_index;
}
