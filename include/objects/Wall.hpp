/*
** EPITECH PROJECT, 2018
** classWall.hpp
** File description:
** classWall declarations
*/

#include <vector>
#include "Positions.hpp"
#include "AObject.hpp"

#ifndef CLASSWALL_HPP_
# define CLASSWALL_HPP_

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
