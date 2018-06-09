//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// AMenu Functions
//

#include <iostream>
#include "AMenu.hpp"
#include "AButton.hpp"

int		AMenu::affButton()
{
	unsigned int		ite = 0;

	while (ite < _buttons.size()) {
		std::cout << this->getButton(ite)->getName() << std::endl;
		ite += 1;
	}
	return 0;
}

AButton		*AMenu::getButton(int pos)
{
	return _buttons.at(pos).get();
}

unsigned int	AMenu::getNbButton()
{
	return _buttons.size() - 1;
}

std::string	AMenu::getName()
{
	return _name;
}
