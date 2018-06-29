/*
** EPITECH PROJECT, 2018
** ACharacter_methods.cpp
** File description:
** ACharacter all methods
*/

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <math.h>
#include <iostream>
#include "Action.hpp"
#include "checkDeath.hpp"
#include "Bomb.hpp"
#include "ACharacter.hpp"
#include "getObject.hpp"

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

void	ACharacter::setSprites(std::vector<std::string> sprites)
{
	_sprites = sprites;
}

void	ACharacter::setOldDir(Action oldDir)
{
	_oldDir = oldDir;
}

void	ACharacter::setOldAction(Action oldAction)
{
	_oldAction = oldAction;
}

void	ACharacter::setBombLiveSprite(std::string liveSprite)
{
	_bombLiveSprites = liveSprite;
}

void	ACharacter::setBombDeathSprite(std::string deathSprite)
{
	_bombDeathSprites = deathSprite;
}

void	ACharacter::setDelayDead(unsigned int delay)
{
	_delayDead = delay;
}

Action	ACharacter::getOldDir()
{
	return _oldDir;
}

Action	ACharacter::getOldAction()
{
	return _oldAction;
}

std::string	ACharacter::getBombLiveSprite()
{
	return _bombLiveSprites;
}

std::string	ACharacter::getBombDeathSprite()
{
	return _bombDeathSprites;
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
	AObject	*bomb = nullptr;

	func_ptr[0] = &ACharacter::moveLeft;
	func_ptr[1] = &ACharacter::moveUp;
	func_ptr[2] = &ACharacter::moveRight;
	func_ptr[3] = &ACharacter::moveDown;
	if (this->_action <= 3 && objects.empty() != true) {
		(*this.*func_ptr[this->_action])(objects);
	} else if (this->_action == Action::PUTBOMB) {
		bomb = this->putBomb(objects);
		return bomb;
	}
	return nullptr;
}

void	ACharacter::checkBonus(std::vector<AObject *> objects)
{
	getObject	get_obj;
	int	object_on_pos = get_obj.getObjectAtPosition(
		round(_position.x + 0.1),
		round(_position.y + 0.4), objects);
	objectType	type = objectType::UNBRWALL;
	bool	hasTaken = false;

	if (object_on_pos == -1)
		return;
	type = objects[object_on_pos]->getObjectType();
	if (type == objectType::BOMBUP) {
		this->_nbrMaxBomb += 1;
		hasTaken = true;
	} else if (type == objectType::FIREUP) {
		if (this->_fireRange < 13)
			this->_fireRange += 1;
		hasTaken = true;
	} else if (type == objectType::SPEEDUP) {
		if (this->_speed < 0.2)
			this->_speed += 0.02;
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
	AObject		*object2 = nullptr;
	Positions	pos = {0, 0};
	Positions	pos2 = {0, 0};
	getObject	get_obj;
	int		idx = get_obj.getObjectAtPosition(
			round(_position.x - 0.4), round(_position.y + 0.1), objects);
	int		idx2 = get_obj.getObjectAtPosition(
			round(_position.x - 0.4), round(_position.y - 0.1), objects);

	if (idx != -1)
		object = objects[idx];
	if (idx2 != -1)
		object2 = objects[idx2];
	pos = (idx != -1) ? (object->getPos()) : (pos);
	pos2 = (idx2 != -1) ? (object2->getPos()) : (pos2);

	if (idx != -1 && (object != nullptr && object->getObjectType() == objectType::BOMB && round(_position.x) <= pos.x) ||
	(idx2 != -1 && object2 != nullptr && object2->getObjectType() == objectType::BOMB && round(_position.x) <= pos2.x))
	{
	} else {
	if ((idx != -1 && _wallPass == false && checkIsBonus(object) != true) ||
	idx2 != -1 && _wallPass == false && checkIsBonus(object2) != true) {
		if (round(_position.y + 0.1) == pos.y ||
		round(_position.y - 0.1) == pos2.y ||
		(this->_position.x - this->_speed) <= (pos.x + 1) ||
		(this->_position.x - this->_speed) <= (pos2.x + 1)
		)
			return ;
	} else if ((idx != -1 && _wallPass == true && checkIsBonus(object) != true) ||
	(idx2 != -1 && _wallPass == true && checkIsBonus(object2) != true)) {
		if ((object != nullptr && object->getObjectType() != objectType::WALL &&
		(round(_position.y + 0.1) == pos.y ||
		(this->_position.x - this->_speed) <= (pos.x + 1))) ||

		(object2 != nullptr && object2->getObjectType() != objectType::WALL &&
		(round(_position.y - 0.1) == pos2.y ||
		(this->_position.x - this->_speed) <= (pos2.x + 1))))
			return ;
	}}
	this->_position.x -= this->_speed;
	this->_position.x = (this->_position.x < 0) ? (0) : (this->_position.x);
}

void	ACharacter::moveRight(std::vector<AObject *> objects)
{
	AObject		*object = nullptr;
	AObject		*object2 = nullptr;
	Positions	pos = {0, 0};
	Positions	pos2 = {0, 0};
	getObject	get_obj;
	int		idx = get_obj.getObjectAtPosition(
			round(_position.x + 0.4), round(_position.y + 0.1), objects);
	int		idx2 = get_obj.getObjectAtPosition(
			round(_position.x + 0.4), round(_position.y - 0.1), objects);

	if (idx != -1)
		object = objects[idx];
	if (idx2 != -1)
		object2 = objects[idx2];
	pos = (idx != -1) ? (object->getPos()) : (pos);
	pos2 = (idx2 != -1) ? (object2->getPos()) : (pos2);
	if (idx != -1 && (object != nullptr && object->getObjectType() == objectType::BOMB && round(_position.x) >= pos.x) ||
	(idx2 != -1 && object2 != nullptr && object2->getObjectType() == objectType::BOMB && round(_position.x) >= pos2.x))
	{
	} else {
	if ((idx != -1 && _wallPass == false && checkIsBonus(object) != true) ||
	idx2 != -1 && _wallPass == false && checkIsBonus(object2) != true) {
		if ((round(_position.y + 0.1) == pos.y ||
		round(_position.y - 0.1) == pos2.y ||
		(this->_position.x + this->_speed) >= (pos.x - 1) ||
		(this->_position.x + this->_speed) >= (pos2.x - 1))) {
			return ;
		}
	} else if ((idx != -1 && _wallPass == true && checkIsBonus(object) != true) ||
		(idx2 != -1 && _wallPass == true && checkIsBonus(object2) != true)) {
		if ((object != nullptr && object->getObjectType() != objectType::WALL &&
		(round(_position.y + 0.1) == pos.y ||
		(this->_position.x + this->_speed) >= (pos.x - 1))) ||

		(object2 != nullptr && object2->getObjectType() != objectType::WALL &&
		(round(_position.y - 0.1) == pos2.y ||
		(this->_position.x + this->_speed) >= (pos2.x - 1)))) {
			return ;
		}
	}
	}
	this->_position.x += this->_speed;
	this->_position.x = (this->_position.x > 12) ? (12) : (_position.x);
}

void	ACharacter::moveUp(std::vector<AObject *> objects)
{
	AObject		*object = nullptr;
	AObject		*object2 = nullptr;
	Positions	pos = {0, 0};
	Positions	pos2 = {0, 0};
	getObject	get_obj;
	int		idx = get_obj.getObjectAtPosition(
			round(_position.x + 0.1), round(_position.y - 0.4), objects);
	int		idx2 = get_obj.getObjectAtPosition(
			round(_position.x - 0.1), round(_position.y - 0.4), objects);

	if (idx != -1)
		object = objects[idx];
	if (idx2 != -1)
		object2 = objects[idx2];
	pos = (idx != -1) ? (object->getPos()) : (pos);
	pos2 = (idx2 != -1) ? (object2->getPos()) : (pos2);
		if (idx != -1 && (object != nullptr && object->getObjectType() == objectType::BOMB && round(_position.y) <= pos.y) ||
	(idx2 != -1 && object2 != nullptr && object2->getObjectType() == objectType::BOMB && round(_position.y) <= pos2.y))
	{
	} else {
	if ((idx != -1  && _wallPass == false && checkIsBonus(object) != true) ||
	idx2 != -1 && _wallPass == false && checkIsBonus(object2) != true) {
		if (round(_position.x + 0.1) == pos.x ||
		round(_position.x - 0.1) == pos2.x ||
		(this->_position.y - this->_speed) <= (pos.y + 1) ||
		(this->_position.y - this->_speed) <= (pos2.y + 1))
			return ;
	} else if ((idx != -1 && object != nullptr && object->getObjectType() != objectType::BOMB && object2 != nullptr && object2->getObjectType() != objectType::BOMB && _wallPass == true && checkIsBonus(object) != true) ||
		(idx2 != -1 && _wallPass == true && checkIsBonus(object2) != true)) {

		if ((object != nullptr && object->getObjectType() != objectType::WALL &&
		(round(_position.x + 0.1) == pos.x ||
		(this->_position.y - this->_speed) <= (pos.y + 1))) ||

		(object2 != nullptr && object2->getObjectType() != objectType::WALL &&
		(round(_position.x - 0.1) == pos2.x ||
		(this->_position.y - this->_speed) <= (pos2.y + 1))))
			return ;
	}
	}
	this->_position.y -= this->_speed;
	this->_position.y = (this->_position.y < 0) ? (0) : (this->_position.y);
}

void	ACharacter::moveDown(std::vector<AObject *> objects)
{
	AObject		*object = nullptr;
	AObject		*object2 = nullptr;
	Positions	pos = {0, 0};
	Positions	pos2 = {0, 0};
	getObject	get_obj;
	int		idx = get_obj.getObjectAtPosition(
			round(_position.x + 0.1), round(_position.y + 0.4), objects);
	int		idx2 = get_obj.getObjectAtPosition(
			round(_position.x - 0.1), round(_position.y + 0.4), objects);

	if (idx != -1)
		object = objects[idx];
	if (idx2 != -1)
		object2 = objects[idx2];
	pos = (idx != -1) ? (object->getPos()) : (pos);
	pos2 = (idx2 != -1) ? (object2->getPos()) : (pos2);
		if (idx != -1 && (object != nullptr && object->getObjectType() == objectType::BOMB && round(_position.y) >= pos.y) ||
	(idx2 != -1 && object2 != nullptr && object2->getObjectType() == objectType::BOMB && round(_position.y) >= pos2.y))
	{
	} else {
	if ((idx != -1 && _wallPass == false && checkIsBonus(object) != true) ||
	idx2 != -1 && _wallPass == false && checkIsBonus(object2) != true) {
		if (round(_position.x + 0.1) == pos.x ||
		round(_position.x - 0.1) == pos2.x ||
		(this->_position.y + this->_speed) >= (pos.y - 1) ||
		(this->_position.y + this->_speed) >= (pos2.y - 1)
		)
			return ;
	} else if ((idx != -1 && _wallPass == true && checkIsBonus(object) != true) ||
		(idx2 != -1 && _wallPass == true && checkIsBonus(object2) != true)) {
		if ((object != nullptr && object->getObjectType() != objectType::WALL &&
		(round(_position.x + 0.1) == pos.x ||
		(this->_position.y + this->_speed) >= (pos.y - 1))) ||

		(object2 != nullptr && object2->getObjectType() != objectType::WALL &&
		(round(_position.x - 0.1) == pos2.x ||
		(this->_position.y + this->_speed) >= (pos2.y - 1))))
			return ;
	}
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
	getObject	get_obj;
	int		idx = get_obj.getObjectAtPosition(
				round(_position.x + 0.1),
				round(_position.y + 0.4), objects);
	Positions	new_pos = { round(this->_position.x),
				round(this->_position.y) };
	AObject		*obj = nullptr;
	Bomb		*bomb(new Bomb(this->_nbrPlayer,
		this->_fireRange, new_pos, this->_bombLiveSprites,
		this->_bombDeathSprites));

	if (objects.empty() != true &&
	this->_nbrPutBomb < this->_nbrMaxBomb && idx == -1) {
		obj = static_cast<AObject *>(bomb);
		obj->setObjectType(objectType::BOMB);
		this->_nbrPutBomb += 1;
		return obj;
	}
	return nullptr;
}

void	ACharacter::checkPlayerDeath(std::vector<AObject *> objects)
{
	Bomb	*bomb = nullptr;
	checkDeath	check;

	for (auto object_it = objects.begin(); object_it != objects.end();
	object_it++) {
		if ((*object_it)->getObjectType() == objectType::BOMB)
			bomb = static_cast<Bomb *>(*object_it);
		if (bomb != nullptr && bomb->getIsDestroyed() == true &&
		check.checkDie(this->_position, bomb->getPos(), bomb) == true) {
			this->_isDead = true;
		}
	}
}
