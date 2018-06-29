/*
** EPITECH PROJECT, 2018
** classBonus.hpp
** File description:
** classBonus declaration
*/

#ifndef BONUS_HPP_
# define BONUS_HPP_

#include <vector>
#include "Positions.hpp"
#include "AObject.hpp"

class	Bonus : public AObject
{
public:
	/* Constructor */
	Bonus(Positions, std::string, objectType);
	void	destroy();
};

#endif /* !BONUS_HPP_ */
