/*
** EPITECH PROJECT, 2018
** Bonus.cpp
** File description:
** Bonus methods
*/

#include "Bonus.hpp"
#include "AObject.hpp"

Bonus::Bonus(Positions pos, std::string lifeSprite, objectType type)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = type;
}

void	Bonus::destroy()
{
	this->_isDestroyed = true;
}
