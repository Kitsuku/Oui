/*
** EPITECH PROJECT, 2018
** classBonus.hpp
** File description:
** classBonus declaration
*/

#include <vector>
#include "Positions.hpp"
#include "AObject.hpp"

#ifndef BONUS_HPP_
# define BONUS_HPP_

class	bonusBombUp : public AObject
{
public:
	/* Constructor */
	bonusBombUp(Positions, std::string);
	void	destroy() {};
};

class	bonusSpeedUp : public AObject
{
public:
	/* Constructor */
	bonusSpeedUp(Positions, std::string);
	void	destroy() {};
};

class	bonusFireUp : public AObject
{
public:
	/* Constructor */
	bonusFireUp(Positions, std::string);
	void	destroy() {};
};

class	bonusWallPass : public AObject
{
public:
	/* Constructor */
	bonusWallPass(Positions, std::string);
	void	destroy() {};
};

#endif /* !BONUS_HPP_ */
