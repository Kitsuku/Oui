//
// EPITECH PROJECT, 2018
// Character temp
// File description:
// Character to load from save file
//

#ifndef CHARACTER_HPP_
# define CHARACTER_HPP_

#include "ACharacter.hpp"

class	Character : public ACharacter
{
public:
	void	defineAction(int, std::vector<AObject *>) {}
};

#endif
