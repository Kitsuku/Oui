//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// DisplayCommandButton functions
//

#include "DisplayCommandButton.hpp"
#include "menu.hpp"
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
	int	check_a = 0;

	_menu = std::move(pause_menu);
	while (graph->begin() && check_a != 2) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		graph->displayBackground("res/Commands.jpg");
		graph->displayText("PRESS A TO GO BACK",
				{1500, 1020, 200, 30}, {100, 255, 255, 255});
		graph->end();
	}
}
