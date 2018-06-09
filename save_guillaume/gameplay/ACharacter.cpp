/*
** EPITECH PROJECT, 2018
** ACharacter_methods.cpp
** File description:
** ACharacter all methods
*/

#include <math.h>
#include <unistd.h>
#include <iostream>
#include "Action.hpp"
#include "checkDie.hpp"
#include "Bomb.hpp"
#include "ACharacter.hpp"
#include "getObjectAtPosition.hpp"

ACharacter::ACharacter(int numberPlayer, Positions pos,
	std::vector<std::string> wanted_sprites,
	std::string bomb_live_sprite, std::string bomb_death_sprite) :
	_nbrPlayer(numberPlayer)
{
	this->_sprites = wanted_sprites;
	this->_bombLiveSprites = bomb_live_sprite;
	this->_bombDeathSprites = bomb_death_sprite;
	this->_position = pos;
	this->_nbrMaxBomb = 1;
	this->_nbrPutBomb = 0;
	this->_fireRange = 2;
	this->_speed = 0.1;
	this->_wallPass = false;
	this->_isDead = false;
	this->_action = IDLE;
}

ACharacter::~ACharacter()
{
}

int	ACharacter::getNbrPlayer()
{
	return _nbrPlayer;
}

bool	ACharacter::getIsDead()
{
	return _isDead;
}

std::unique_ptr<AObject>	ACharacter::doAction(
					std::vector<AObject *> objects)
{
	void	(ACharacter::*func_ptr[5])(std::vector<AObject *>);
	std::unique_ptr<AObject>	bomb(new Bomb(this->_nbrPlayer,
					this->_fireRange,
					this->_position, this->_bombLiveSprites,
					this->_bombDeathSprites));

	func_ptr[0] = &ACharacter::moveLeft;
	func_ptr[1] = &ACharacter::moveRight;
	func_ptr[2] = &ACharacter::moveUp;
	func_ptr[3] = &ACharacter::moveDown;
	if (this->_action <= 3) {
		(*this.*func_ptr[this->_action])(objects);
		bomb.reset();
		return nullptr;
	} else if (this->_action == Action::PUTBOMB)
		bomb = this->putBomb(objects);
	return bomb;
}

Positions	ACharacter::getPos()
{
	return _position;
}

Action		ACharacter::getAction()
{
	return this->_action;
}

std::vector<std::string>	ACharacter::getSprites()
{
	return this->_sprites;
}

void	ACharacter::checkBonus(std::vector<AObject *> objects)
{
	int	object_on_pos = getObjectAtPosition(
		floor(_position.x), floor(_position.y), objects);
	objectType	type = objects[object_on_pos]->getObjectType();

	if (type == objectType::BOMBUP) {
		this->_nbrMaxBomb += 1;
	} else if (type == objectType::FIREUP) {
		this->_fireRange += 1;
	} else if (type == objectType::SPEEDUP) {
		this->_speed += 0.1;
	}
	_wallPass = (type == objectType::WALLPASS) ?
		(_wallPass = true) : (false);
}

bool	checkIsBonus(AObject *object)
{
	if (object->getObjectType() != objectType::BOMBUP ||
	object->getObjectType() != objectType::SPEEDUP ||
	object->getObjectType() != objectType::FIREUP ||
	object->getObjectType() != objectType::WALLPASS)
		return true;
	return false;
}

void	ACharacter::moveLeft(std::vector<AObject *> objects)
{
	AObject		*object;
	Positions	pos;
	int		idx = getObjectAtPosition(
		floor(_position.x) - 1, floor(_position.y), objects);

	object = (idx != -1) ? (objects[idx]) : (object);
	pos = (idx != -1) ? (object->getPos()) : (pos);
	if (idx != -1 && _wallPass == false) {
		if (floor(_position.y) != pos.y ||
		(this->_position.x - this->_speed) <= (pos.x + 1))
			return ;
	} else if (idx != -1 && _wallPass == true) {
		if (object->getObjectType() != objectType::WALL &&
		checkIsBonus(object) != true &&
		(floor(_position.y) != pos.y ||
		(this->_position.x - this->_speed) <= (pos.x + 1)))
			return ;
	}
	this->_position.x -= this->_speed;
	this->_position.x = (this->_position.x < 0) ? (0) : (this->_position.x);
}

void	ACharacter::moveRight(std::vector<AObject *> objects)
{
	AObject		*object;
	Positions	pos;
	int		idx = getObjectAtPosition(
		ceil(_position.x) + 1, floor(_position.y), objects);

	object = (idx != -1) ? (objects[idx]) : (object);
	pos = (idx != -1) ? (object->getPos()) : (pos);
	if (idx != -1 && _wallPass == false) {
		if (floor(_position.y) != pos.y ||
		(_position.x + _speed) >= (pos.x - 1))
			return ;
	} else if (idx != -1 && _wallPass == true) {
		if (object->getObjectType() != objectType::WALL &&
		checkIsBonus(object) != true &&
		(floor(_position.y) != pos.y ||
		(_position.x + _speed) >= (pos.x - 1)))
			return ;
	}
	this->_position.x += this->_speed;
	this->_position.x = (this->_position.x > 12) ? (12) : (_position.x);
}

void	ACharacter::moveUp(std::vector<AObject *> objects)
{
	AObject		*object;
	Positions	pos;
	int		idx = getObjectAtPosition(
		floor(_position.x), floor(_position.y) - 1, objects);

	object = (idx != -1) ? (objects[idx]) : (object);
	pos = (idx != -1) ? (object->getPos()) : (pos);
	if (idx != -1 && _wallPass == false) {
		if (floor(_position.x) != pos.x ||
		(this->_position.y - this->_speed) <= (pos.y + 1))
			return ;
	} else if (idx != -1 && _wallPass == true) {
		if (object->getObjectType() != objectType::WALL &&
		checkIsBonus(object) != true &&
		(floor(_position.x) != pos.x ||
		(this->_position.y - this->_speed) <= (pos.y + 1)))
			return ;
	}
	this->_position.y -= this->_speed;
	this->_position.y = (this->_position.y < 0) ? (0) : (this->_position.y);
}

void	ACharacter::moveDown(std::vector<AObject *> objects)
{
	AObject		*object;
	Positions	pos;
	int		idx = getObjectAtPosition(
		floor(_position.x), ceil(_position.y) + 1, objects);

	object = (idx != -1) ? (objects[idx]) : (object);
	pos = (idx != -1) ? (object->getPos()) : (pos);
	if (idx != -1 && _wallPass == false) {
		if (floor(_position.x) != pos.x ||
		(this->_position.y + this->_speed) >= (pos.y - 1))
			return ;
	} else if (idx != -1 && _wallPass == true) {
		if (object->getObjectType() != objectType::WALL &&
		checkIsBonus(object) != true &&
		(floor(_position.x) != pos.x ||
		(this->_position.y + this->_speed) >= (pos.y - 1)))
			return ;
	}
	this->_position.y += this->_speed;
	_position.y = (_position.y > 10) ? (10) : (_position.y);
}

void	ACharacter::removePutBomb()
{
	if (this->_nbrPutBomb > 0)
		this->_nbrPutBomb -= 1;
}

std::unique_ptr<AObject>	ACharacter::putBomb(
				std::vector<AObject *> objects)
{
	int		idx = getObjectAtPosition(
				floor(_position.x),
				floor(_position.y), objects);
	std::unique_ptr<AObject>	new_bomb(new Bomb(this->_nbrPlayer,
					this->_fireRange,
					this->_position, this->_bombLiveSprites,
					this->_bombDeathSprites));

	this->_action = Action::IDLE;
	if (this->_nbrPutBomb < this->_nbrMaxBomb && idx == -1) {
		this->_nbrPutBomb += 1;
		return new_bomb;
	}
	new_bomb.reset();
	return nullptr;
}

void	ACharacter::checkDeath(std::vector<AObject *> objects)
{
	Bomb	*bomb = nullptr;

	for (auto object_it = objects.begin(); object_it != objects.end();
	object_it++) {
		if ((*object_it)->getObjectType() == objectType::BOMB)
			bomb = static_cast<Bomb *>(*object_it);
		if (bomb != nullptr && bomb->getIsDestroyed() == true &&
		checkDie(this->_position, bomb->getPos(), bomb) == true) {
			this->_isDead = true;
		}
	}
}