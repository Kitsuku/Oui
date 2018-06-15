//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// AMenu class
//

#ifndef AMENU_HPP_
# define AMENU_HPP_

#include <vector>
#include <memory>
#include <iostream>
#include "Graphics.hpp"

class AButton;

class AMenu
{
public:
	int		affButton(Graphics *, int);
	AButton		*getButton(int);
	unsigned int	getNbButton();
	std::string	getName();
	void		displayButtonBox(Graphics *, int, unsigned int);
	void		displayButtonName(Graphics *, unsigned int);
	virtual void		displayButton(Graphics *, int);
protected:
	std::vector<std::unique_ptr<AButton>>	_buttons;
	std::string				_name;
};

#endif /* !AMENU_HPP_ */
