/*
** EPITECH PROJECT, 2018
** checkDeath.hpp
** File description:
** checkDeath declaration
*/

#ifndef CHECKDEATH_HPP_
# define CHECKDEATH_HPP_

#include "Positions.hpp"
#include "Bomb.hpp"

class	checkDeath
{
public:
	bool	checkDieX(Positions, Positions, Bomb *);
	bool	checkDieY(Positions, Positions, Bomb *);
	bool	checkDie(Positions, Positions, Bomb *);
};

#endif /* !CHECKDEATH_HPP_ */
