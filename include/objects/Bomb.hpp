/*
** EPITECH PROJECT, 2018
** classBomb.hpp
** File description:
** classBomb declarations
*/

#include <time.h>
#include <vector>
#include "Positions.hpp"
#include "enumObjectType.hpp"
#include "AObject.hpp"

#ifndef CLASSBOMB_HPP_
# define CLASSBOMB_HPP_

class	Bomb : public AObject
{
public:
	/* Constructor */
	Bomb(int, int, Positions, std::string, std::string);
	Bomb();
	/* Bomb Methods */
	void	checkTime();
	void	destroy();
	void	checkHitWall(Positions);
	void	updatePower(AObject *);
	void	updateTimer(AObject *);
	time_t	getTime();
	int	getPower(std::string);
	int	getNbrPlayer();
	unsigned int			getDelayDead();
	void				addDelayDead();
	void	setTime(time_t);
	void	setPower(std::string, int);
	void	setNbrPlayer(int);


protected:
	unsigned int		_delayDead;
	int	_nbrPlayer;
	time_t	_time;
	int	_power_default;
	int	_power_up;
	int	_power_down;
	int	_power_left;
	int	_power_right;
	
};

#endif /* !CLASSBOMB_HPP_ */
