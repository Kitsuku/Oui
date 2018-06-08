/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** abstract class character
*/

#include <vector>
#include "action.hpp"
#include "objects/AObject.hpp"

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

class	ACharacter
{
public:
	/* Constructor */
	ACharacter(int, pos);
	/* Destructor */
	~ACharacter();
	/* Methods */
	virtual void		defineAction(int,
		std::vector<AObject *> &objects) const = 0;
	void			doAction(Action, std::vector<AObject *>);
	Positions		getPos();
	std::vector<int>	getSprites(std::string);
	void			moveLeft(std::vector<AObject *>);
	void			moveUp(std::vector<AObject *>);
	void			moveRight(std::vector<AObject *>);
	void			moveDown(std::vector<AObject *>);
	void			putBomb(std::vector<AObject *>);

protected:
	int			_nbrPlayer;
	int			_nbrBomb;
	int			_fireRange;
	float			_speed;
	bool			_wallPass;
	Positions		_position;
	std::vector<int>	_leftSprites;
	std::vector<int>	_rightSprites;
	std::vector<int>	_upSprites;
	std::vector<int>	_downSprites;
};

#endif
