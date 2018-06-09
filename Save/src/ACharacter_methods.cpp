/*
** EPITECH PROJECT, 2018
** ACharacter_methods.cpp
** File description:
** ACharacter all methods
*/

#include <math.h>
#ifdef linux
#include <unistd.h>
#endif
#ifdef _WIN32
#include <io.h>
#endif
#include <iostream>
#include "ACharacter.hpp"
#include "getObjectAtPosition.hpp"

ACharacter::ACharacter(int nbPlayer, Positions pos) : _nbrPlayer(nbPlayer), _position(pos)
{
}

ACharacter::~ACharacter()
{
}

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

void	ACharacter::moveLeft(std::vector<AObject *> objects)
{
	AObject		*object_on_left;
	Positions	object_pos;
	int		index_object = getObjectAtPosition(
				floor(_position.x) - 1,
				floor(_position.y), objects);

	if (index_object != -1) {
		object_on_left = objects[index_object];
		object_pos = object_on_left->getPos();
		if (floor(_position.y) != object_pos.y ||
		(this->_position.x - this->_speed) <= (object_pos.x + 1))
			return ;
	}
	this->_position.x -= this->_speed;
	if (this->_position.x < 0)
		this->_position.x = 0;
}

void	ACharacter::moveRight(std::vector<AObject *> objects)
{
	AObject		*object_on_right;
	Positions	object_pos;
	int		index_object = getObjectAtPosition(
				ceil(_position.x) + 1,
				floor(_position.y), objects);

	if (index_object != -1) {
		object_on_right = objects[index_object];
		object_pos = object_on_right->getPos();
		if (floor(_position.y) != object_pos.y ||
		(this->_position.x + this->_speed) >= (object_pos.x - 1))
			return ;
	}
	this->_position.x += this->_speed;
	if (this->_position.x > 13)
		this->_position.x = 13;
}

void	ACharacter::moveUp(std::vector<AObject *> objects)
{
	AObject		*object_on_down;
	Positions	object_pos;
	int		index_object = getObjectAtPosition(
				floor(_position.x),
				floor(_position.y) - 1, objects);

	if (index_object != -1) {
		object_on_down = objects[index_object];
		object_pos = object_on_down->getPos();
		if (floor(_position.x) != object_pos.x ||
		(this->_position.y - this->_speed) <= (object_pos.y + 1))
			return ;
	}
	this->_position.y -= this->_speed;
	if (this->_position.y < 0)
		this->_position.y = 0;
}

void	ACharacter::moveDown(std::vector<AObject *> objects)
{
	AObject		*object_on_down;
	Positions	object_pos;
	int		index_object = getObjectAtPosition(
				floor(_position.x),
				ceil(_position.y) + 1, objects);

	if (index_object != -1) {
		object_on_down = objects[index_object];
		object_pos = object_on_down->getPos();
		if (floor(_position.x) != object_pos.x ||
		(this->_position.y + this->_speed) >= (object_pos.y - 1))
			return ;
	}
	this->_position.y += this->_speed;
	if (this->_position.y > 11)
		this->_position.y = 11;
}
