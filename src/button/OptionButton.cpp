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

	std::cerr << "Action bouton début" << std::endl;
	_menu = std::move(option);
	std::cerr << "move option" << std::endl;
	//graph = graph;
	std::cerr << "fin" << std::endl;
}
