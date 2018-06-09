//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// StartButton functions
//

#include "StartButton.hpp"
#include "MainMenu.hpp"

StartButton::StartButton()
{
	_name = "Start";
}

StartButton::~StartButton()
{
}

void	StartButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> main (new MainMenu);

	_menu = std::move(main);
	//Appelle de méthode play
}
