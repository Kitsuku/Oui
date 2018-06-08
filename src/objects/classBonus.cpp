/*
** EPITECH PROJECT, 2018
** classBonus.hpp
** File description:
** classBonus functions
*/

#include "classBonus.hpp"

bonusBombUp::bonusBombUp(Positions pos, std::vector<int> lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::BOMBUP;
}

bonusSpeedUp::bonusSpeedUp(Positions pos, std::vector<int> lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::SPEEDUP;
}

bonusFireUp::bonusFireUp(Positions pos, std::vector<int> lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::FIREUP;
}

bonusWallPass::bonusWallPass(Positions pos, std::vector<int> lifeSprite)
{
	this->_livingSprites = lifeSprite;
	this->_isDestroyed = false;
	this->_position = pos;
	this->_objectType = objectType::WALLPASS;
}
