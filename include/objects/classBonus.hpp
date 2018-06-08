/*
** EPITECH PROJECT, 2018
** classBonus.hpp
** File description:
** classBonus declaration
*/

#include <vector>
#include "positions.hpp"
#include "AObject.hpp"

#ifndef BONUS_HPP_
# define BONUS_HPP_

class	bonusBombUp : public AObject
{
public:
	/* Constructor */
	bonusBombUp(Positions, std::vector<int>);
};

class	bonusSpeedUp : public AObject
{
public:
	/* Constructor */
	bonusSpeedUp(Positions, std::vector<int>);
};

class	bonusFireUp : public AObject
{
public:
	/* Constructor */
	bonusFireUp(Positions, std::vector<int>);
};

class	bonusWallPass : public AObject
{
public:
	/* Constructor */
	bonusWallPass(Positions, std::vector<int>);
};

#endif /* !BONUS_HPP_ */
