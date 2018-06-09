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

class AButton;

class AMenu
{
public:
	int		affButton(/*lib graph*/);
	AButton		*getButton(int);
	unsigned int	getNbButton();
	std::string	getName();
protected:
	std::vector<std::unique_ptr<AButton>>	_buttons;
	std::string				_name;
};

#endif /* !AMENU_HPP_ */
