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
	bool	isSafeWay(std::vector<AObject *>);
	int	bombIsHere(std::vector<AObject *>);
	void	timeToRun(std::vector<AObject *>);
	void	isThereAWall(std::vector<AObject *>);
	bool	isNextToWall(std::vector<AObject *>);
};

#endif
