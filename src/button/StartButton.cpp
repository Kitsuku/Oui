//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// StartButton functions
//

#include "StartButton.hpp"
#include "MainMenu.hpp"
#include "Map.hpp"

StartButton::StartButton()
{
	_name = "Start";
}

StartButton::~StartButton()
{
}

void	StartButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> main = std::make_unique<MainMenu>();
	Map	map(13, 11, graph->getPath());

	_menu = std::move(main);
	map.generateMap();
	map.generateCharacter(1);
	map.setSpriteGroundAndBackGround();
	map.play(graph);
}
