/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** class IA
*/

#ifndef IA_HPP_
# define IA_HPP_

#include <irrlicht.h>
#include "ACharacter.hpp"
#include "AObject.hpp"
#include "Bomb.hpp"

class	IA: public ACharacter
{
public:
	IA(int, Positions, std::vector<std::string>, std::string, std::string);
	~IA();
	AObject	*defineAction(const irr::SEvent::SJoystickEvent &,
			std::vector<AObject *>);
	int	checkFire(AObject *);
	int	inBombRange(std::vector<AObject *> );
	int	checkThisPosition(std::vector<AObject *> , int, int);
	int	safePosition(AObject *, std::vector<AObject *>);
	int	otherSafePosition(AObject *, std::vector<AObject *>, int);
	int	moveAwayFromThisPosition(std::vector<AObject *>);
	int	moveFromThisPosition(std::vector<AObject *>);
	int	justMoove(std::vector<AObject *>);
	int	checkAround(std::vector<AObject *>, int, int);
	int	checkFireRangeUP(Bomb *, float, float);
	int	checkFireRangeDown(Bomb *, float, float);
	int	checkFireRangeRight(Bomb *, float, float);
	int	checkFireRangeLeft(Bomb *, float, float);
};

#endif
