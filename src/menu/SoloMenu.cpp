//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SoloMenu functions
//

#include "SoloMenu.hpp"
#include "SoloGroundButton.hpp"
#include "BackGroundSoloButton.hpp"
#include "StartSoloButton.hpp"
#include "ReturnMPButton.hpp"

SoloMenu::SoloMenu()
{
	std::unique_ptr<AButton> start = std::make_unique<StartSoloButton>();
	std::unique_ptr<AButton> ground = std::make_unique<SoloGroundButton>();
	std::unique_ptr<AButton> background = std::make_unique<BackGroundSoloButton>();
	std::unique_ptr<AButton> return_mm = std::make_unique<ReturnMmButton>();

	_buttons.push_back(std::move(start));
	_buttons.push_back(std::move(ground));
	_buttons.push_back(std::move(background));
	_buttons.push_back(std::move(return_mm));
}

SoloMenu::~SoloMenu()
{
}
