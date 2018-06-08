/*
** EPITECH PROJECT, 2018
** classBomb.hpp
** File description:
** classBomb declarations
*/

#include <time.h>
#include <vector>
#include "positions.hpp"
#include "enumObjectType.hpp"
#include "AObject.hpp"

#ifndef CLASSBOMB_HPP_
# define CLASSBOMB_HPP_

class	Bomb : public AObject
{
public:
	/* Constructor */
	Bomb(int, Positions, std::vector<int>, std::vector<int>);
	/* Bomb Methods */
	void	checkTime();
	void	destroy();
	int	getPower(std::string);
	void	checkHitWall(Positions);
	void	updatePower(AObject *);
	void	updateTimer(AObject *);

protected:
	time_t	_time;
	int	_power_default;
	int	_power_up;
	int	_power_down;
	int	_power_left;
	int	_power_right;
};

#endif /* !CLASSBOMB_HPP_ */
