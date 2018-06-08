/*
** EPITECH PROJECT, 2018
** classBomb.hpp
** File description:
** classBomb functions
*/

#include <iostream>
#include "classBomb.hpp"

Bomb::Bomb(int given_power, Positions pos,
	std::vector<int> lifeSprite, std::vector<int> deathSprite)
{
	time(&(this->_time));
	this->_power_default = given_power;
	this->_power_up = given_power;
	this->_power_down = given_power;
	this->_power_left = given_power;
	this->_power_right = given_power;
	this->_livingSprites = lifeSprite;
	this->_dyingSprites = deathSprite;
	this->_isDestroyed = false;
	this->_objectType = objectType::BOMB;
	this->_position = pos;
}

void	Bomb::checkTime()
{
	double	seconds;
	time_t	now;

	time(&now);
	seconds = difftime(now, this->_time);
	if (seconds >= 3)
		this->destroy();
}

void	Bomb::destroy()
{
	// appelle affichage
	std::cout << "BOMB destroying (call aff method)" << std::endl;
	this->_isDestroyed = true;
}

int	Bomb::getPower(std::string asked)
{
	if (asked.compare("default") == 0)
		return this->_power_default;
	if (asked.compare("up") == 0)
		return this->_power_up;
	else if (asked.compare("down") == 0)
		return this->_power_down;
	else if (asked.compare("left") == 0)
		return this->_power_left;
	return this->_power_right;
}
