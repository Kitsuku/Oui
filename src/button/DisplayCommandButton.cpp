//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// DisplayCommandButton functions
//

#include "DisplayCommandButton.hpp"
#include "PauseMenu.hpp"

DisplayCommandButton::DisplayCommandButton()
{
	_name = "Command";
}

DisplayCommandButton::~DisplayCommandButton()
{
}

void	DisplayCommandButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> pause_menu (new PauseMenu);

	_menu = std::move(pause_menu);
	graph = graph;
	//Appel displaySprite
}
