/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** method of the class IA
*/

#ifdef WIN32
#define __attribute__(A)
#endif
#include "enumObjectType.hpp"
#include "Bomb.hpp"
#include "IA.hpp"
#include <iostream>

IA::IA(int numberPlayer, Positions pos,
	std::vector<std::string> wanted_sprites,
	std::string bomb_live_sprite, std::string bomb_death_sprite) :
	ACharacter(numberPlayer, pos, wanted_sprites,
		bomb_live_sprite, bomb_death_sprite)
{
}

IA::~IA()
{
}

int	IA::checkFireRangeUP(Bomb *bomb, float pos_x, float pos_y)
{
	int	power = bomb->getPower("up");
	Positions	pos = bomb->getPos();

	if (floor(pos_x) == floor(pos.x) &&
	pos_y <= pos.y + power && pos_y >= pos.y)
		return 1;
	return 0;
}

int	IA::checkFireRangeDown(Bomb *bomb, float pos_x, float pos_y)
{
	int	power = bomb->getPower("down");
	Positions	pos = bomb->getPos();

	if (floor(pos_x) == floor(pos.x) &&
	pos_y >= pos.y - power && pos_y <= pos.y)
		return 1;
	return 0;
}

int	IA::checkFireRangeRight(Bomb *bomb, float pos_x, float pos_y)
{
	int	power = bomb->getPower("right");
	Positions	pos = bomb->getPos();

	if (pos_x <= pos.x + power && pos_x >= pos.x &&
		floor(pos_y) == floor(pos.y))
		return 1;
	return 0;
}

int	IA::checkFireRangeLeft(Bomb *bomb, float pos_x, float pos_y)
{
	int	power = bomb->getPower("right");
	Positions	pos = bomb->getPos();

	if (pos_x >= pos.x - power && pos_x <= pos.x &&
		floor(pos_y) == floor(pos.y))
		return 1;
	return 0;
}

int	IA::checkFire(AObject *object)
{
	Bomb		*bomb = static_cast<Bomb*>(object);

	if (checkFireRangeUP(bomb, floor(_position.x),
		floor(_position.y)) == 1 ||
		checkFireRangeDown(bomb, floor(_position.x),
		floor(_position.y)) == 1 ||
		checkFireRangeRight(bomb, floor(_position.x),
		floor(_position.y)) == 1 ||
		checkFireRangeLeft(bomb, floor(_position.x),
		floor(_position.y)) == 1)
		return 1;
	return 0;
}

int	IA::inBombRange(std::vector<AObject *> objects)
{
	std::vector<AObject *>::iterator	ite;
	int					bomb = 0;

	for (ite = objects.begin(); ite != objects.end(); ite++) {
		if ((*ite)->getObjectType() == BOMB)
			bomb = 1;
		if (bomb == 1 && checkFire(*ite) == 1) {
			safePosition(*ite, objects);
			return 1;
		}
	}
	return 0;
}

int	IA::checkThisPosition(std::vector<AObject *> objects,
	int pos_x, int pos_y)
{
	Positions				position;
	std::vector<AObject *>::iterator	ite;
	objectType				type;
	int					position_x;
	int					position_y;

	for (ite = objects.begin(); ite != objects.end(); ite += 1) {
		position = (*ite)->getPos();
		position_x = floor(position.x);
		position_y = floor(position.y);
		type = (*ite)->getObjectType();
		if (((position_x == pos_x && position_y == pos_y) &&
			(type == BOMB || type == UNBRWALL ||
			(type == WALL && _wallPass == false))) ||
			pos_x < 0 || pos_x > 12 || pos_y < 0 || pos_y > 10) {
			return 0;
		}
	}
	return 1;
}

int	IA::safePosition(AObject *object, std::vector<AObject *> objects)
{
	Positions	position = object->getPos();
	Bomb		*bomb = static_cast<Bomb*>(object);
	int		power = bomb->getPower("default");

	for (int ite = 0; ite != power; ite++) {
		if (position.x + ite == _position.x + 1 &&
		checkThisPosition(objects,
		floor(_position.x), floor(_position.y) + 1) == 1) {
			_action = UP;
			return 0;
		} else if (position.x - ite == _position.x - 1 &&
			checkThisPosition(objects,
			floor(_position.x), floor(_position.y) - 1) == 1) {
			_action = DOWN;
			return 0;
		} else if (otherSafePosition(object, objects, ite) == 1)
			return 0;
	}
	return 0;
}

int	IA::otherSafePosition(AObject *object, std::vector<AObject *> objects,
	int ite)
{
	Positions	position = object->getPos();

	if (position.y + ite == _position.y &&
		checkThisPosition(objects,
		floor(_position.x) + 1, floor(_position.y)) == 1) {
		_action = RIGHT;
		return 1;
	} else if (position.y - ite == _position.y &&
		checkThisPosition(objects,
		floor(_position.x) - 1, floor(_position.y)) == 1) {
		_action = LEFT;
		return 1;
	}
	return 0;
}

int	IA::moveAwayFromThisPosition(std::vector<AObject *> objects)
{
	if (checkThisPosition(objects, floor(_position.x) + 1,
		floor(_position.y)) == 1) {
		_action = RIGHT;
		return 1;
	} else if (checkThisPosition(objects, floor(_position.x) - 1,
		floor(_position.y)) == 1) {
 		_action = LEFT;
		return 1;
	}
	return 0;
}

int	IA::moveFromThisPosition(std::vector<AObject *> objects)
{
	if (checkThisPosition(objects, floor(_position.x),
		floor(_position.y) - 1) == 1) {
		_action = UP;
		return 1;
	} else if (checkThisPosition(objects, floor(_position.x),
		floor(_position.y) + 1) == 1) {
		_action = DOWN;
		return 1;
	}
	return moveAwayFromThisPosition(objects);
}

int	IA::checkAround(std::vector<AObject *> objects, int pos_x, int pos_y)
{
	int	check = 0;

	check += checkThisPosition(objects, pos_x + 1,
	pos_y);
	check += checkThisPosition(objects, pos_x - 1,
	pos_y);
	check += checkThisPosition(objects, pos_x,
	pos_y + 1);
	check += checkThisPosition(objects, pos_x,
	pos_y - 1);
	return check;
}

int	IA::justMoove(std::vector<AObject *> objects)
{
	if (checkThisPosition(objects, floor(_position.x),
		floor(_position.y)) == 0)
		return moveFromThisPosition(objects);
	else if (checkAround(objects, floor(_position.x),
		floor(_position.y)) > 1)
		return moveFromThisPosition(objects);
	return 0;
}

AObject	*IA::defineAction(__attribute__((unused)) const
	irr::SEvent::SJoystickEvent &key, std::vector<AObject *> objects)
{
	int	action = 0;

	if (inBombRange(objects) == 1)
		action = 1;
	else if (justMoove(objects) == 1)
		action = 1;
	if (action == 0 && _nbrMaxBomb != _nbrPutBomb)
		_action = PUTBOMB;
	return doAction(objects);
}
