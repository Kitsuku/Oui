/*
** EPITECH PROJECT, 2018
** classWall.hpp
** File description:
** classWall declarations
*/

#ifndef CLASSWALL_HPP_
# define CLASSWALL_HPP_

#include <vector>
#include "Positions.hpp"
#include "AObject.hpp"

class	Wall : public AObject
{
public:
	/* Constructor */
	Wall(Positions, std::string, std::string);
	/* Methods */
	void	checkBreak(AObject *);
	void	destroy();
};

#endif /* !CLASSWALL_HPP_ */
