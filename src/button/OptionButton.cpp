//
// EPITECH PROJECT, 2018
// IndieStudio
// File description:
// OptionButton Functions
//

#include "OptionButton.hpp"
#include "OptionMenu.hpp"

OptionButton::OptionButton()
{
	_name = "Option";
}

OptionButton::~OptionButton()
{
}

void	OptionButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> option (new OptionMenu);

	_menu = std::move(option);
	graph = graph;
}
