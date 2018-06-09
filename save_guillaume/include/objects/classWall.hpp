/*
** EPITECH PROJECT, 2018
** classWall.hpp
** File description:
** classWall declarations
*/

#include <vector>
#include "positions.hpp"
#include "AObject.hpp"

#ifndef CLASSWALL_HPP_
# define CLASSWALL_HPP_

class	Wall : public AObject
{
public:
	/* Constructor */
	Wall(Positions, std::vector<int>, std::vector<int>);
	/* Methods */
	void	checkBreak(AObject *);
	void	destroy();
};

#endif /* !CLASSWALL_HPP_ */
