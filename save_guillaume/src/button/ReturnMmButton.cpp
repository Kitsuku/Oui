//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// ReturnMmButton functions
//

#include "ReturnMPButton.hpp"
#include "MainMenu.hpp"

ReturnMmButton::ReturnMmButton()
{
	_name = "Return";
}

ReturnMmButton::~ReturnMmButton()
{
}

void	ReturnMmButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> main (new MainMenu);

	_menu = std::move(main);
}
