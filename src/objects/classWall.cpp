/*
** EPITECH PROJECT, 2018
** classWall.hpp
** File description:
** classWall functions
*/

#include <iostream>
#include "checkDie.hpp"
#include "classWall.hpp"

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
