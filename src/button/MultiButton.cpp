//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// MultiButton functions
//

#include "MultiButton.hpp"
#include "MultiMenu.hpp"

MultiButton::MultiButton()
{
	_name = "Multi";
}

MultiButton::~MultiButton()
{
}

void	MultiButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> multi = std::make_unique<MultiMenu>();

	_menu = std::move(multi);
	graph = graph;
}
