//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// RulesButton functions
//

#include "RulesButton.hpp"
#include "PauseMenu.hpp"

RulesButton::RulesButton()
{
	_name = "Rules";
}

RulesButton::~RulesButton()
{
}

void	RulesButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> pause (new PauseMenu);

	_menu = std::move(pause);
	//Appel DisplaySprite
}
