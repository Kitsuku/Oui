//
// EPITECH PROJECT, 2018
// Character temp
// File description:
// Character to load from save file
//

#ifndef IA_HPP_
# define IA_HPP_

#include "ACharacter.hpp"

class	IA : public ACharacter
{
public:
	IA(int nbrPlayer, Positions pos, std::vector<std::string> sprites,
	std::string livingBomb, std::string dyingBomb) : ACharacter(nbrPlayer, pos, sprites, livingBomb, dyingBomb) {}
	void	defineAction(const irr::SEvent::SJoystickEvent &, std::vector<AObject *>) {}
};

#endif
