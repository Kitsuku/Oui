//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// OptionMenu functions
//

#include "OptionMenu.hpp"
#include "SoundButton.hpp"
#include "SaveGestionButton.hpp"
#include "ReturnMPButton.hpp"

OptionMenu::OptionMenu()
{
	std::unique_ptr<AButton> sound  = std::make_unique<SoundButton>();
	std::unique_ptr<AButton> save = std::make_unique<SaveGestionButton>();
	std::unique_ptr<AButton> return_mm = std::make_unique<ReturnMmButton>();

	_buttons.push_back(std::move(sound));
	_buttons.push_back(std::move(save));
	_buttons.push_back(std::move(return_mm));
}

OptionMenu::~OptionMenu()
{
}
