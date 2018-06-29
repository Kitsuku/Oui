/*
** EPITECH PROJECT, 2018
** classUnbrWall.hpp
** File description:
** classUnbrWall declaration
*/

#ifndef CLASSUNBRWALL_HPP_
# define CLASSUNBRWALL_HPP_

#include <vector>
#include "Positions.hpp"
#include "AObject.hpp"

class	UnbrWall : public AObject
{
public:
	/* Constructor */
	UnbrWall(Positions, std::string);
	void	destroy() {};
};

#endif /* !CLASSUNBRWALL_HPP_ */
