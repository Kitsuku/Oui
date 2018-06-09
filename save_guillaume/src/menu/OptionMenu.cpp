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
	std::unique_ptr<AButton> sound (new SoundButton);
	std::unique_ptr<AButton> save (new SaveGestionButton);
	std::unique_ptr<AButton> return_mm (new ReturnMmButton);

	_buttons.push_back(std::move(sound));
	_buttons.push_back(std::move(save));
	_buttons.push_back(std::move(return_mm));
}

OptionMenu::~OptionMenu()
{
}
