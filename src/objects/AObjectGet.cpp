/*
** EPITECH PROJECT, 2018
** AObjectget.cpp
** File description:
** AObject get functions
*/

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
