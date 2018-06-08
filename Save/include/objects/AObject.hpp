/*
** EPITECH PROJECT, 2018
** AObject.hpp
** File description:
** AObject declaration
*/

#include <time.h>
#include <vector>
#include <memory>
#include "positions.hpp"
#include "enumObjectType.hpp"

#ifndef AOBJECT_HPP_
# define AOBJECT_HPP_

class	AObject
{
public:
	/* Methods */
	virtual void		destroy() = 0;
	objectType		getObjectType();
	std::vector<int>	getLivingSprites();
	std::vector<int>	getDyingSprites();
	Positions		getPos();
	bool			getIsDestroyed();
	void			setObjectType(objectType);
	void			setLivingSprites(std::vector<int>);
	void			setDyingSprites(std::vector<int>);
	void			setPos(Positions);
	void			setIsDestroyed(bool isDestroyed) { _isDestroyed = isDestroyed; }

protected:
	objectType		_objectType;
	std::vector<int>	_livingSprites;
	std::vector<int>	_dyingSprites;
	Positions		_position;
	bool			_isDestroyed;
};

#endif /* !AOBJECT_HPP_ */
