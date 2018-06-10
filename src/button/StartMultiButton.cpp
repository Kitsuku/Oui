//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// StartButton functions
//

#include "StartMultiButton.hpp"
#include "MainMenu.hpp"
#include "Map.hpp"

StartMultiButton::StartMultiButton()
{
	_name = "Start";
}

StartMultiButton::~StartMultiButton()
{
}

void	StartMultiButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> main (new MainMenu);
	Map	map(1, 1);

	_menu = std::move(main);
	map.generateMap();
	map.generateCharacter(2);
	map.setSpriteGroundAndBackGround();
	map.play(graph);
}
