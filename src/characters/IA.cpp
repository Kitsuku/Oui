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

	if (floor(pos_x) == floor(pos.x) && pos_y <= pos.y + power &&
		pos_y >= pos.y)
		return 1;
	return 0;
}

int	IA::checkFireRangeDown(Bomb *bomb, float pos_x, float pos_y)
{
	int	power = bomb->getPower("down");
	Positions	pos = bomb->getPos();

	if (floor(pos_x) == floor(pos.x) && pos_y >= pos.y - power &&
		pos_y <= pos.y)
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
		return 4;
	return 0;
}

int	IA::checkFire(AObject *object)
{
	Bomb		*bomb = static_cast<Bomb*>(object);

	if (checkFireRangeUP(bomb, floor(_position.x),
		floor(_position.y)) != 0)
		return 1;
	else if (checkFireRangeDown(bomb, floor(_position.x),
		floor(_position.y)) != 0)
		return 2;
	else if (checkFireRangeRight(bomb, floor(_position.x),
		floor(_position.y)) != 1)
		return 3;
	return checkFireRangeLeft(bomb, floor(_position.x), floor(_position.y));
}

int	IA::inBombRange(std::vector<AObject *> objects)
{
	std::vector<AObject *>::iterator	ite;
	int					bomb = 0;
	int					fire = 0;

	for (ite = objects.begin(); ite != objects.end(); ite++) {
		if ((*ite)->getObjectType() == BOMB)
			bomb = 1;
		fire = checkFire(*ite);
		if (bomb == 1 && fire != 0) {
			safePosition(*ite, objects, fire);
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

void	IA::checkPosUP(Bomb *bomb, std::vector<AObject *> objects)
{
	if (checkThisPosition(objects, checkPosX(floor(_position.x)) - 1,
		checkPosY(floor(_position.y))) == 1)
		_action = Action::LEFT;
	else if (checkThisPosition(objects, checkPosX(floor(_position.x)) + 1,
		checkPosY(floor(_position.y))) == 1)
		_action = Action::RIGHT;
	else if (checkThisPosition(objects, checkPosX(floor(_position.x)),
		checkPosY(floor(_position.y)) - 1) == 1)
		_action = Action::UP;
}

void	IA::checkPosDown(Bomb *bomb, std::vector<AObject *> objects)
{
	if (checkThisPosition(objects, checkPosX(floor(_position.x)) - 1,
		checkPosY(floor(_position.y))) == 1)
		_action = Action::LEFT;
	else if (checkThisPosition(objects, checkPosX(floor(_position.x)) + 1,
		checkPosY(floor(_position.y))) == 1)
		_action = Action::RIGHT;
	else if (checkThisPosition(objects, checkPosX(floor(_position.x)),
		checkPosY(floor(_position.y)) + 1) == 1)
		_action = Action::DOWN;
}

void	IA::checkPosRight(Bomb *bomb, std::vector<AObject *> objects)
{
	if (checkThisPosition(objects, checkPosX(floor(_position.x)),
		checkPosY(floor(_position.y)) - 1) == 1)
		_action = Action::UP;
	else if (checkThisPosition(objects, checkPosX(floor(_position.x)),
		checkPosY(floor(_position.y)) + 1) == 1)
		_action = Action::DOWN;
	else if (checkThisPosition(objects, checkPosX(floor(_position.x)) + 1,
		checkPosY(floor(_position.y))) == 1)
		_action = Action::RIGHT;
}

void	IA::checkPosLeft(Bomb *bomb, std::vector<AObject *> objects)
{
	if (checkThisPosition(objects, checkPosX(floor(_position.x)),
		checkPosY(floor(_position.y)) - 1) == 1)
		_action = Action::UP;
	else if (checkThisPosition(objects, checkPosX(floor(_position.x)),
		checkPosY(floor(_position.y)) + 1) == 1)
		_action = Action::DOWN;
	else if (checkThisPosition(objects, checkPosX(floor(_position.x)) - 1,
		checkPosY(floor(_position.y))) == 1)
		_action = Action::LEFT;
}

void	IA::safePosition(AObject *object, std::vector<AObject *> objects,
			int fire)
{
	Bomb		*bomb = static_cast<Bomb*>(object);

	if (fire == 1)
		checkPosUP(bomb, objects);
	else if (fire == 2)
		checkPosDown(bomb, objects);
	else if (fire == 3)
		checkPosRight(bomb, objects);
	checkPosLeft(bomb, objects);
}

int	IA::moveAwayFromThisPosition(std::vector<AObject *> objects,
	int pos_x, int pos_y)
{
	if (checkThisPosition(objects, pos_x + 1, pos_y) == 1) {
		std::cout << "IA nb " << _nbrPlayer << " move right" << std::endl;
		_action = Action::RIGHT;
		return 1;
	} else if (checkThisPosition(objects, pos_x - 1, pos_y) == 1) {
		std::cout << "IA nb " << _nbrPlayer << " move left" << std::endl;
 		_action = Action::LEFT;
		return 1;
	}
	return 0;
}

int	IA::moveFromThisPosition(std::vector<AObject *> objects,
	int pos_x, int pos_y)
{
	if (checkThisPosition(objects, pos_x, pos_y - 1) == 1) {
		std::cout << "IA nb " << _nbrPlayer << " move up" << std::endl;
		_action = Action::UP;
		return 1;
	} else if (checkThisPosition(objects, pos_x, pos_y + 1) == 1) {
		_action = Action::DOWN;
		std::cout << "IA nb " << _nbrPlayer << " move down" << std::endl;
		return 1;
	}
	return moveAwayFromThisPosition(objects, pos_x, pos_y);
}

int	IA::checkPosX(int pos_x)
{
	if (pos_x < _position.x && _action == Action::LEFT)
		pos_x += 1;
	return pos_x;
}

int	IA::checkPosY(int pos_y)
{
	if (pos_y < _position.y && _action == Action::UP)
		pos_y += 1;
	return pos_y;
}

int	IA::checkAround(std::vector<AObject *> objects, int pos_x, int pos_y)
{
	int	check = 0;

	pos_x = checkPosX(pos_x);
	pos_y = checkPosY(pos_y);
	check += checkThisPosition(objects, pos_x + 1, pos_y);
	check += checkThisPosition(objects, pos_x - 1, pos_y);
	check += checkThisPosition(objects, pos_x, pos_y + 1);
	check += checkThisPosition(objects, pos_x, pos_y - 1);
	std::cout << "check : " << check << std::endl;
	return check;
}

int	IA::justMoove(std::vector<AObject *> objects)
{
	if (checkThisPosition(objects, floor(_position.x),
		floor(_position.y)) == 0)
		return moveFromThisPosition(objects,
		checkPosX(floor(_position.x)), checkPosY(floor(_position.y)));
	else if (inBombRange(objects) == 1)
		return 1;
	else if (checkAround(objects, floor(_position.x),
		floor(_position.y)) > 1)
		return moveFromThisPosition(objects,
		checkPosX(floor(_position.x)), checkPosY(floor(_position.y)));
	std::cout << "IA nb : " << _nbrPlayer << " can't move" << std::endl;
	return 0;
}

void	IA::modifyPos()
{
	if (_position.x - floor(_position.x) > 0.09 &&
		_position.x - floor(_position.x) < 0.1)
		_position.x =  floor(_position.x);
	if (_position.y - floor(_position.y) > 0.09 &&
		_position.y - floor(_position.y) < 0.1)
		_position.y =  floor(_position.y);
}

AObject	*IA::defineAction(__attribute__((unused)) const
	irr::SEvent::SJoystickEvent &key, std::vector<AObject *> objects)
{
	int	action = 0;

	std::cout << "IA nbr : " << _nbrPlayer << " pos : " << _position.x << " " << _position.y << std::endl;
	modifyPos();
	if (justMoove(objects) == 1)
		action = 1;
/*	if (action == 0 && _nbrMaxBomb != _nbrPutBomb)
		_action = Action::PUTBOMB;*/
	return doAction(objects);
}
