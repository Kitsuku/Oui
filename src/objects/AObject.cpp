/*
** EPITECH PROJECT, 2018
** AObjects_methods.cpp
** File description:
** AObjects methods
*/

#include <iostream>
#include "AObject.hpp"

objectType		AObject::getObjectType()
{
	return this->_objectType;
}

std::string	AObject::getLivingSprites()
{
	return this->_livingSprites;
}

std::string	AObject::getDyingSprites()
{
	return this->_dyingSprites;
}

Positions	AObject::getPos()
{
	return this->_position;
}

bool	AObject::getIsDestroyed()
{
	return this->_isDestroyed;
}

void	AObject::setObjectType(objectType type)
{
	this->_objectType = type;
}

void	AObject::setLivingSprites(std::string sprite)
{
	this->_livingSprites = sprite;
}

void	AObject::setDyingSprites(std::string sprite)
{
	this->_dyingSprites = sprite;
}

void	AObject::setPos(Positions pos)
{
	this->_position = pos;
}

void	AObject::setIsDestroyed(bool dead)
{
	this->_isDestroyed = dead;
}
