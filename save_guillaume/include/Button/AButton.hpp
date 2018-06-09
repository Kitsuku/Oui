//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// AButton class
//

#ifndef ABUTTON_HPP_
# define ABUTTON_HPP_

#include <string>
#include <memory>
#include "Graphics.hpp"

class AMenu;

class AButton
{
public:
	virtual void	action(Graphics *) = 0;
	AMenu		*getBMenu();
	std::string	getName();
protected:
	std::unique_ptr<AMenu> 	_menu;
	std::string    		_name;
};

#endif /* !ABUTTON_HPP_ */
