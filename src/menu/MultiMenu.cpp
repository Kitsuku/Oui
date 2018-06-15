//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// MultiMenu functions
//

#include "MultiMenu.hpp"
#include "MultiGroundButton.hpp"
#include "BackGroundMultiButton.hpp"
#include "StartMultiButton.hpp"
#include "ReturnMPButton.hpp"

MultiMenu::MultiMenu()
{
	std::unique_ptr<AButton> start (new StartMultiButton);
	std::unique_ptr<AButton> ground (new MultiGroundButton);
	std::unique_ptr<AButton> background (new BackGroundMultiButton);
	std::unique_ptr<AButton> return_mm (new ReturnMmButton);

	_buttons.push_back(std::move(start));
	_buttons.push_back(std::move(ground));
	_buttons.push_back(std::move(background));
	_buttons.push_back(std::move(return_mm));
}

MultiMenu::~MultiMenu()
{
}
