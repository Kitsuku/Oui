/*
** EPITECH PROJECT, 2018
** getObject.hpp
** File description:
** getObject declaration
*/

#ifndef GETOBJECT_HPP_
# define GETOBJECT_HPP_

#include <vector>
#include "AObject.hpp"

class	getObject
{
public:
	int	getObjectAtPosition(float, float, std::vector<AObject *>);
};

#endif /* !GETOBJECT_HPP_ */
