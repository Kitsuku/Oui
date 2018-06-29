/*
** EPITECH PROJECT, 2018
** Wall.cpp
** File description:
** Wall methods
*/

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include "Wall.hpp"
#include "Bomb.hpp"
#include "checkDeath.hpp"
#include "AObject.hpp"
#include <exception>

Wall::Wall(Positions pos, std::string lifeSprite,
	std::string deathSprite)
{
	this->_livingSprites = lifeSprite;
	this->_dyingSprites = deathSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::WALL;
}

void	Wall::checkBreak(AObject *object)
{
	Bomb	*bomb = nullptr;
	checkDeath	check_death;
	objectType	type;

	if (object == nullptr)
	 	return ;
	type = object->getObjectType();
	if (object->getObjectType() == objectType::BOMB &&
	object->getIsDestroyed() == true) {
		bomb = static_cast<Bomb *>(object);
		if (bomb != nullptr &&
		check_death.checkDie(_position, bomb->getPos(), bomb)) {
			this->destroy();
		}
	}
}

void	Wall::destroy()
{
	this->_isDestroyed = true;
}
