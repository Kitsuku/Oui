/*
** EPITECH PROJECT, 2018
** AObject.hpp
** File description:
** AObject declaration
*/

#ifndef AOBJECT_HPP_
# define AOBJECT_HPP_

#include <time.h>
#include <vector>
#include <memory>
#include "Positions.hpp"
#include "enumObjectType.hpp"

class	AObject
{
public:
	/* Methods */
	virtual void		destroy() = 0;
	objectType		getObjectType();
	std::string		getLivingSprites();
	std::string		getDyingSprites();
	Positions		getPos();
	bool			getIsDestroyed();
	void			setObjectType(objectType);
	void			setLivingSprites(std::string);
	void			setDyingSprites(std::string);
	void			setPos(Positions);
	void			setIsDestroyed(bool);

protected:
	objectType		_objectType;
	std::string		_livingSprites;
	std::string		_dyingSprites;
	Positions		_position;
	bool			_isDestroyed;
};

#endif /* !AOBJECT_HPP_ */
