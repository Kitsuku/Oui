//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SoloMenu functions
//

#include "SoloMenu.hpp"
#include "GroundButton.hpp"
#include "BackGroundButton.hpp"
#include "StartButton.hpp"
#include "ReturnMPButton.hpp"

SoloMenu::SoloMenu()
{
	std::unique_ptr<AButton> ground (new GroundButton);
	std::unique_ptr<AButton> background (new BackGroundButton);
	std::unique_ptr<AButton> start (new StartButton);
	std::unique_ptr<AButton> return_mm (new ReturnMmButton);

	_buttons.push_back(std::move(ground));
	_buttons.push_back(std::move(background));
	_buttons.push_back(std::move(start));
	_buttons.push_back(std::move(return_mm));
}

SoloMenu::~SoloMenu()
{
}
