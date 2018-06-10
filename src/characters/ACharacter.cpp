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
	this->_delayDead = 0;
}

ACharacter::ACharacter()
{
}

ACharacter::~ACharacter()
{
}

void	ACharacter::setNbrPlayer(int nbr)
{
	this->_nbrPlayer = nbr;
}

void	ACharacter::setPos(Positions pos)
{
	this->_position = pos;
}

void	ACharacter::setNbrMaxBomb(int nbr)
{
	this->_nbrMaxBomb = nbr;
}

void	ACharacter::setNbrPutBomb(int nbr)
{
	this->_nbrPutBomb = nbr;
}

void	ACharacter::setSpeed(float wanted_speed)
{
	this->_speed = wanted_speed;
}

void	ACharacter::setWallPass(bool isWallPass)
{
	this->_wallPass = isWallPass;
}

void	ACharacter::setIsDead(bool dead)
{
	this->_isDead = dead;
}

void	ACharacter::setAction(Action act)
{
	this->_action = act;
}

void	ACharacter::setFireRange(int power)
{
	this->_fireRange = power;
}

void	ACharacter::setSprites(std::vector<std::string>)
{
}

Positions	ACharacter::getPos()
{
	return this->_position;
}

std::vector<std::string>	ACharacter::getSprites()
{
	return this->_sprites;
}

Action	ACharacter::getAction()
{
	return this->_action;
}

int	ACharacter::getNbrMaxBomb()
{
	return this->_nbrMaxBomb;
}

int	ACharacter::getNbrPutBomb()
{
	return this->_nbrPutBomb;
}

float	ACharacter::getSpeed()
{
	return this->_speed;
}

bool	ACharacter::getWallPass()
{
	return this->_wallPass;
}
int	ACharacter::getFireRange()
{
	return this->_fireRange;
}

int	ACharacter::getNbrPlayer()
{
	return _nbrPlayer;
}

bool	ACharacter::getIsDead()
{
	return _isDead;
}

unsigned int			ACharacter::getDelayDead()
{
	return _delayDead;
}

void				ACharacter::addDelayDead()
{
	++_delayDead;
}


AObject	*ACharacter::doAction(std::vector<AObject *> objects)
{
	void	(ACharacter::*func_ptr[5])(std::vector<AObject *>);
	AObject	*bomb;

	func_ptr[0] = &ACharacter::moveLeft;
	func_ptr[1] = &ACharacter::moveUp;
	func_ptr[2] = &ACharacter::moveRight;
	func_ptr[3] = &ACharacter::moveDown;
	if (this->_action <= 3) {
		(*this.*func_ptr[this->_action])(objects);
	} else if (this->_action == Action::PUTBOMB) {
		bomb = this->putBomb(objects);
		//this->_action = Action::IDLE;
		return bomb;
	}
	//this->_action = Action::IDLE;
	return nullptr;
}

void	ACharacter::checkBonus(std::vector<AObject *> objects)
{
	int	object_on_pos = getObjectAtPosition(
		floor(_position.x), floor(_position.y), objects);
	objectType	type = objectType::UNBRWALL;
	bool	hasTaken = false;

	if (object_on_pos == -1)
		return;
	type = objects[object_on_pos]->getObjectType();
	if (type == objectType::BOMBUP) {
		this->_nbrMaxBomb += 1;
		hasTaken = true;
	} else if (type == objectType::FIREUP) {
		this->_fireRange += 1;
		hasTaken = true;
	} else if (type == objectType::SPEEDUP) {
		this->_speed += 0.1;
		hasTaken = true;
	} else if (type == objectType::WALLPASS) {
		_wallPass = true;
		hasTaken = true;
	}
	if (hasTaken == true)
		objects[object_on_pos]->destroy();
}

bool	checkIsBonus(AObject *object)
{
	if (object->getObjectType() == objectType::BOMBUP ||
	object->getObjectType() == objectType::SPEEDUP ||
	object->getObjectType() == objectType::FIREUP ||
	object->getObjectType() == objectType::WALLPASS)
		return true;
	return false;
}

void	ACharacter::moveLeft(std::vector<AObject *> objects)
{
	AObject		*object = nullptr;
	Positions	pos = {0, 0};
	int		idx = getObjectAtPosition(
		floor(_position.x) - 1, floor(_position.y), objects);

	if (idx != -1)
		object = objects[idx];
	pos = (idx != -1) ? (object->getPos()) : (pos);
	if (idx != -1 && _wallPass == false && checkIsBonus(object) != true) {
		if (floor(_position.y) != pos.y ||
		(this->_position.x - this->_speed) <= (pos.x + 1))
			return ;
	} else if (idx != -1 && _wallPass == true && checkIsBonus(object) != true) {
		if (object->getObjectType() != objectType::WALL &&
		(floor(_position.y) != pos.y ||
		(this->_position.x - this->_speed) <= (pos.x + 1)))
			return ;
	}
	this->_position.x -= this->_speed;
	this->_position.x = (this->_position.x < 0) ? (0) : (this->_position.x);
}

void	ACharacter::moveRight(std::vector<AObject *> objects)
{
	AObject		*object = nullptr;
	Positions	pos = {0, 0};
	int		idx = getObjectAtPosition(
		floor(_position.x) + 1, floor(_position.y), objects);

	if (idx != -1)
		object = objects[idx];
	pos = (idx != -1) ? (object->getPos()) : (pos);
	if (idx != -1 && _wallPass == false && checkIsBonus(object) != true) {
		if (floor(_position.y) != pos.y ||
		(_position.x + _speed) >= (pos.x - 1))
			return ;
	} else if (idx != -1 && _wallPass == true && checkIsBonus(object) != true) {
		if (object->getObjectType() != objectType::WALL &&
		(floor(_position.y) != pos.y ||
		(_position.x + _speed) >= (pos.x - 1)))
			return ;
	}
	this->_position.x += this->_speed;
	this->_position.x = (this->_position.x > 12) ? (12) : (_position.x);
}

void	ACharacter::moveUp(std::vector<AObject *> objects)
{
	AObject		*object = nullptr;
	Positions	pos = {0, 0};
	int		idx = getObjectAtPosition(
		floor(_position.x), floor(_position.y) - 1, objects);

	if (idx != -1)
		object = objects[idx];
	pos = (idx != -1) ? (object->getPos()) : (pos);
	if (idx != -1 && _wallPass == false && checkIsBonus(object) != true) {
		if (floor(_position.x) != pos.x ||
		(this->_position.y - this->_speed) <= (pos.y + 1))
			return ;
	} else if (idx != -1 && _wallPass == true && checkIsBonus(object) != true) {
		if (object->getObjectType() != objectType::WALL &&
		(floor(_position.x) != pos.x ||
		(this->_position.y - this->_speed) <= (pos.y + 1)))
			return ;
	}
	this->_position.y -= this->_speed;
	this->_position.y = (this->_position.y < 0) ? (0) : (this->_position.y);
}

void	ACharacter::moveDown(std::vector<AObject *> objects)
{
	AObject		*object = nullptr;
	Positions	pos = {0, 0};
	int		idx = getObjectAtPosition(
		floor(_position.x), floor(_position.y) + 1, objects);

	if (idx != -1)
		object = objects[idx];
	pos = (idx != -1) ? (object->getPos()) : (pos);
	if (idx != -1 && _wallPass == false && checkIsBonus(object) != true) {
		if (floor(_position.x) != pos.x ||
		(this->_position.y + this->_speed) >= (pos.y - 1))
			return ;
	} else if (idx != -1 && _wallPass == true && checkIsBonus(object) != true) {
		if (object->getObjectType() != objectType::WALL &&
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

AObject	*ACharacter::putBomb(std::vector<AObject *> objects)
{
	int		idx = getObjectAtPosition(
				floor(_position.x),
				floor(_position.y), objects);
	Positions	new_pos = { round(this->_position.x),
				round(this->_position.y) };
	AObject		*obj;
	Bomb		*bomb(new Bomb(this->_nbrPlayer,
		this->_fireRange, new_pos, this->_bombLiveSprites,
		this->_bombDeathSprites));

	if (this->_nbrPutBomb < this->_nbrMaxBomb && idx == -1) {
		obj = static_cast<AObject *>(bomb);
		this->_nbrPutBomb += 1;
		return obj;
	}
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
