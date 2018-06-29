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

bool	isBomb(objectType type)
{
	if (type == BOMB)
		return true;
	return false;
}

bool    isUnbrWall(objectType type)
{
	if (type == UNBRWALL)
                return true;
        return false;
}

int	searchInMap(std::vector<AObject *> objects, float x, float y)
{
	int	tempIt = 0;
	Positions	cpy;

	if (x > 12 || x < 0 || y > 10 || y < 0)
		return -3;
	for (auto it = objects.begin(); it != objects.end(); it += 1) {
		cpy = objects.at(tempIt)->getPos();
		if (cpy.x == x &&
		    cpy.y == y &&
		    objects.at(tempIt)->getObjectType() == WALL)
			return 1;
		else if (cpy.x == x &&
			 cpy.y == y &&
			 isBomb(objects.at(tempIt)->getObjectType()))
			return -1;
		else if (cpy.x == x &&
                         cpy.y == y &&
                         isUnbrWall(objects.at(tempIt)->getObjectType()))
			return -2;
		tempIt += 1;
	}
	return 0;
}

bool	WallOnTheLeft(std::vector<AObject *> objects, Positions pos)
{
	int	cpyX = pos.x;
	int	cpyY = pos.y;

	while (cpyX >= 0) {
		switch (searchInMap(objects, cpyX, cpyY))
                {
	        case 1 : return true;
                case -1 : return false;
                case -2 : return false;
                case -3 : return false;
                }
		cpyX -= 1;
	}
	return false;
}

bool	WallOnTheRight(std::vector<AObject *> objects, Positions pos)
{
        int	cpyX = pos.x;
        int	cpyY = pos.y;

        while (cpyX <= 12) {
		switch (searchInMap(objects, cpyX, cpyY))
                {
	        case 1 : return true;
                case -1 : return false;
                case -2 : return false;
                case -3 : return false;
                }
                cpyX += 1;
        }
        return false;
}

bool	WallOnTheTop(std::vector<AObject *> objects, Positions pos)
{
        int	cpyX = pos.x;
        int	cpyY = pos.y;

        while (cpyY >= 0) {
		switch (searchInMap(objects, cpyX, cpyY))
		{
		case 1 : return true;
		case -1 : return false;
		case -2 : return false;
		case -3 : return false;
		}
                cpyY -= 1;
        }
        return false;
}

bool	WallOnTheBot(std::vector<AObject *> objects, Positions pos)
{
        int	cpyX = pos.x;
        int	cpyY = pos.y;

        while (cpyY <= 10) {
		switch (searchInMap(objects, cpyX, cpyY))
                {
	        case 1 : return true;
                case -1 : return false;
                case -2 : return false;
                case -3 : return false;
                }
                cpyY += 1;
        }
        return false;
}

void	IA::isThereAWall(std::vector<AObject *> objects)
{
	Positions       cpy = _position;

	cpy.x = round(cpy.x);
	cpy.y = round(cpy.y);
	if (WallOnTheLeft(objects, cpy)) {
		_action = LEFT;
		_oldDir = RIGHT;
	}
	else if (WallOnTheRight(objects, cpy)) {
		_action = RIGHT;
		_oldDir = LEFT;
        }
	else if (WallOnTheTop(objects, cpy)) {
		_action = UP;
		_oldDir = DOWN;
        }
	else if (WallOnTheBot(objects, cpy)) {
		_action = DOWN;
		_oldDir = UP;
        }
}

bool	IA::isNextToWall(std::vector<AObject *> objects)
{
	Positions	cpy = _position;

	cpy.x = round(cpy.x);
	cpy.y = round(cpy.y);
	if (_action == LEFT && cpy.x > 0) {
		if (searchInMap(objects, cpy.x - 1, cpy.y) == 1) {
			return true;
		}
	}
	if (_action == RIGHT && cpy.x < 12) {
		if (searchInMap(objects, cpy.x + 1, cpy.y) == 1)
			return true;
	}
	if (_action == UP && cpy.y > 0) {
		if (searchInMap(objects, cpy.x, cpy.y - 1) == 1)
			return true;
	}
	if (_action == DOWN && cpy.y < 10) {
		if (searchInMap(objects, cpy.x, cpy.y + 1) == 1)
			return true;
	}
	return false;
}

void	IA::timeToRun(std::vector<AObject *> objects)
{
	_action = _oldDir;
	_oldAction = PUTBOMB;
	if (_action == LEFT)
		_oldDir == RIGHT;
	else if (_action == RIGHT)
		_oldDir = LEFT;
	else if (_action == UP)
		_oldDir = DOWN;
	else if (_action == DOWN)
		_oldDir = UP;
}

bool	IA::isSafeWay(std::vector<AObject *> objects)
{
	int	posX;
        int	posY;

	posX = floor(_position.x);
	posY = floor(_position.y);	
	if (_action == LEFT || _action == RIGHT) {
		if (posY > 0 && searchInMap(objects, posX, posY - 1) == 0) {
			_oldAction = _action;
			_action = UP;
			_oldDir = DOWN;
			return true;
		}
		else if (posY < 10 && searchInMap(objects, posX, posY + 1) == 0) {
			_oldAction = _action;
			_action = DOWN;
			_oldDir = UP;
			return true;
		}
	}
	else if (_action == UP || _action == DOWN) {
		if (posX < 12 && searchInMap(objects, posX + 1, posY) == 0) {
			_oldAction = _action;
                        _action	= RIGHT;
			_oldDir = LEFT;
			return true;
	        }	
                else if	(posX > 0 && searchInMap(objects, posX - 1, posY) == 0) {
			_oldAction = _action;
                        _action	= LEFT;
			_oldDir = RIGHT;
			return true;
                }
	}
	return false;
}

AObject	*IA::defineAction(__attribute__((unused)) const
			  irr::SEvent::SJoystickEvent &key, std::vector<AObject *> objects)
{
	//Le joueur vient de poser une bombe et doit s'en aller
	if (_action == PUTBOMB) {
		timeToRun(objects);
	}
	//Le joueur est entrain de partir, il doit trouver un endroit pour se mettre à l'abri
	else if (_oldAction == PUTBOMB) {
                isSafeWay(objects);
	}
	//Si le joueur est entrain de courir et qu'il n'est pas prêt d'un mur
	else if (_oldAction != PUTBOMB && isNextToWall(objects) == false) {
		isThereAWall(objects);
	}
	//Si le joueur est au contact d'un mur
	else if (isNextToWall(objects) == true) {
		if (_nbrMaxBomb > _nbrPutBomb) {
			_action = PUTBOMB;
		}
		else
			_oldAction = IDLE;
	}
	return doAction(objects);
}
