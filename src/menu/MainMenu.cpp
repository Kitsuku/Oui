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
	std::unique_ptr<AButton> play = std::make_unique<PlayButton>();
	std::unique_ptr<AButton> option = std::make_unique<OptionButton>();
	std::unique_ptr<AButton> exit = std::make_unique<ExitButton>();

	_buttons.push_back(std::move(play));
	_buttons.push_back(std::move(option));
	_buttons.push_back(std::move(exit));
}

MainMenu::~MainMenu()
{
}

void	MainMenu::displayButton(Graphics *graph, int ite_button)
{
	graph->displayImage("res/Bomberman_artwork.png", {25, 360, 700, 700});
	graph->displayImage("res/Bomberman_Title.png", {300, 25, 1280, 355});
	this->affButton(graph, ite_button);
}
