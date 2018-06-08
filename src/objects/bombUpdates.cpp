/*
** EPITECH PROJECT, 2018
** bombUpdates.hpp
** File description:
** updates functions for class Bomb
*/

#include <iostream>
#include "checkDie.hpp"
#include "classBomb.hpp"

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
