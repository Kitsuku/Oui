//
// EPITECH PROJECT, 2018
// Character temp
// File description:
// Character to load from save file
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include "ACharacter.hpp"

class	Player : public ACharacter
{
public:
	void	defineAction(int, std::vector<AObject *>) {}
};

#endif
