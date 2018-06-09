/*
** EPITECH PROJECT, 2018
** UnbrWall.cpp
** File description:
** UnbrWall methods
*/

#include "UnbrWall.hpp"
#include "AObject.hpp"

UnbrWall::UnbrWall(Positions pos, std::string lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::UNBRWALL;
}
