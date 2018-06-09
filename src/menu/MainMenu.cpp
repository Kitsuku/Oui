//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// MainMenu Functions
//

#include "MainMenu.hpp"
#include "PlayButton.hpp"
#include "OptionButton.hpp"
#include "ExitButton.hpp"

MainMenu::MainMenu()
{
	std::unique_ptr<AButton> play (new PlayButton);
	std::unique_ptr<AButton> option (new OptionButton);
	std::unique_ptr<AButton> exit (new ExitButton);

	_buttons.push_back(std::move(play));
	_buttons.push_back(std::move(option));
	_buttons.push_back(std::move(exit));
}

MainMenu::~MainMenu()
{
}
