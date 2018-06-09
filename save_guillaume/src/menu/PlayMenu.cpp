//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// PlayMenu functions
//

#include "PlayMenu.hpp"
#include "SoloButton.hpp"
#include "MultiButton.hpp"
#include "LoadButton.hpp"
#include "ReturnMPButton.hpp"

PlayMenu::PlayMenu()
{
	std::unique_ptr<AButton> solo (new SoloButton);
	std::unique_ptr<AButton> multi (new MultiButton);
	std::unique_ptr<AButton> load (new LoadButton);
	std::unique_ptr<AButton> return_mm (new ReturnMmButton);

	_buttons.push_back(std::move(solo));
	_buttons.push_back(std::move(multi));
	_buttons.push_back(std::move(load));
	_buttons.push_back(std::move(return_mm));
}

PlayMenu::~PlayMenu()
{
}
