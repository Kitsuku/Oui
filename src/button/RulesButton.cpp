//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// RulesButton functions
//

#include "RulesButton.hpp"
#include "menu.hpp"
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
	std::unique_ptr<AMenu> pause = std::make_unique<PauseMenu>();
	int	check_a;

	_menu = std::move(pause);
	while (graph->begin() && check_a != 2) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		graph->displayBackground("res/Rules.png");
		graph->displayText("PRESS A TO GO BACK",
				{1500, 60, 200, 30}, {100, 255, 255, 255});
		graph->end();
	}
}
