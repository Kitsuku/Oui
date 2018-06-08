/*
** EPITECH PROJECT, 2018
** classUnbrWall.hpp
** File description:
** classUnbrWall functions
*/

#include "classUnbrWall.hpp"

UnbrWall::UnbrWall(Positions pos, std::vector<int> lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::UNBRWALL;
}
