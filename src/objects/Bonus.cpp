/*
** EPITECH PROJECT, 2018
** Bonus.cpp
** File description:
** Bonus methods
*/

#include "Bonus.hpp"
#include "AObject.hpp"

bonusBombUp::bonusBombUp(Positions pos, std::string lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::BOMBUP;
}

bonusSpeedUp::bonusSpeedUp(Positions pos, std::string lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::SPEEDUP;
}

bonusFireUp::bonusFireUp(Positions pos, std::string lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::FIREUP;
}

bonusWallPass::bonusWallPass(Positions pos, std::string lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::WALLPASS;
}
