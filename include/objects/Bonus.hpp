/*
** EPITECH PROJECT, 2018
** classBonus.hpp
** File description:
** classBonus declaration
*/

#include <vector>
#include "Positions.hpp"
#include "AObject.hpp"

#ifndef BONUS_HPP_
# define BONUS_HPP_

class	Bonus : public AObject
{
public:
	/* Constructor */
	Bonus(Positions, std::string, objectType);
	void	destroy();
};

#endif /* !BONUS_HPP_ */
