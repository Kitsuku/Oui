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
<<<<<<< HEAD
	/* Bomb Methods */
	void	checkTime();
	void	destroy();
=======
	Bomb() {}
	/* Bomb Methods */
	void	checkTime();
	void	destroy();
	time_t	getTime() { return _time; }
>>>>>>> origin/Paul/generation_map
	int	getPower(std::string);
	void	checkHitWall(Positions);
	void	updatePower(AObject *);
	void	updateTimer(AObject *);
<<<<<<< HEAD
=======
	void	setTime(time_t time) { _time = time; }
	void	setDefaultPower(int power) { _power_default = power; }
	void	setUpPower(int power) { _power_up = power; }
	void	setDownPower(int power) { _power_down = power; }
	void	setLeftPower(int power) { _power_left = power; }
	void	setRightPower(int power) { _power_right = power; }
>>>>>>> origin/Paul/generation_map

protected:
	time_t	_time;
	int	_power_default;
	int	_power_up;
	int	_power_down;
	int	_power_left;
	int	_power_right;
};

#endif /* !CLASSBOMB_HPP_ */
