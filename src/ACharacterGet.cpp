/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** method of the abstract class character
*/

#include "ACharacter.hpp"

Positions	ACharacter::getPos()
{
	return _position;
}

std::vector<int>	ACharacter::getSprites(std::string wanted)
{
	if (wanted.compare("left") == 0)
		return this->_leftSprites;
	else if (wanted.compare("right") == 0)
		return this->_rightSprites;
	else if (wanted.compare("up") == 0)
		return this->_upSprites;
	return this->_downSprites;
}
