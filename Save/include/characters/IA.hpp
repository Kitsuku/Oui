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
	void	defineAction(int, std::vector<AObject *>) {}
};

#endif
