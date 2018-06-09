//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// QuitButton functions
//

#include "QuitButton.hpp"
#include "MainMenu.hpp"

QuitButton::QuitButton()
{
	_name = "Quit";
}

QuitButton::~QuitButton()
{
}

void	QuitButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> main (new MainMenu);

	_menu = std::move(main);
}
