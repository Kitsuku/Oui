//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// PlayButton
//

#include "PlayButton.hpp"
#include "PlayMenu.hpp"

PlayButton::PlayButton()
{
	_name = "Play";
}

PlayButton::~PlayButton()
{
}

void	PlayButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> play_menu (new PlayMenu);

	_menu = std::move(play_menu);
}
