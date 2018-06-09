//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// AButton functions
//

#include "AButton.hpp"

AMenu	*AButton::getBMenu()
{
	return _menu.get();
}

std::string	AButton::getName()
{
	return _name;
}
