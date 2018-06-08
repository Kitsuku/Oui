/*
** EPITECH PROJECT, 2018
** AObjectSet.cpp
** File description:
** AObject set functions
*/

#include "AObject.hpp"

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
