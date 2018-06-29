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
	std::unique_ptr<AButton> start = std::make_unique<StartMultiButton>();
	std::unique_ptr<AButton> ground = std::make_unique<MultiGroundButton>();
	std::unique_ptr<AButton> background = std::make_unique<BackGroundMultiButton>();
	std::unique_ptr<AButton> return_mm = std::make_unique<ReturnMmButton>();

	_buttons.push_back(std::move(start));
	_buttons.push_back(std::move(ground));
	_buttons.push_back(std::move(background));
	_buttons.push_back(std::move(return_mm));
}

MultiMenu::~MultiMenu()
{
}
