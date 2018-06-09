/*
** EPITECH PROJECT, 2018
** classUnbrWall.hpp
** File description:
** classUnbrWall declaration
*/

#include <vector>
#include "positions.hpp"
#include "AObject.hpp"

#ifndef CLASSUNBRWALL_HPP_
# define CLASSUNBRWALL_HPP_

class	UnbrWall : public AObject
{
public:
	/* Constructor */
	UnbrWall(Positions, std::vector<int>);
};

#endif /* !CLASSUNBRWALL_HPP_ */
