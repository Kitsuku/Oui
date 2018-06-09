//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// ResumeButton functions
//

#include "PauseMenu.hpp"
#include "ResumeButton.hpp"
#include "menu.hpp"

ResumeButton::ResumeButton()
{
	_name = "Resume";
}

ResumeButton::~ResumeButton()
{
}

void	ResumeButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu>	menu_pause (new PauseMenu);
	AMenu		*menu = menu_pause.get();
	unsigned int	ite_button = 0;
	int		check_a = 0;

	while (menu && graph->run()) {
		const std::vector<irr::SEvent::SJoystickEvent>
                        &joystickData = graph->getController();
                ite_button = MoveButtonFromMenu(ite_button, menu, joystickData);
                check_a = ButtonUnpressed(joystickData, check_a, 0);
                if (check_a == 2) {
                        menu->affButton();
                        menu->getButton(ite_button)->action(graph);
                        menu = menu->getButton(ite_button)->getBMenu();
                        ite_button = 0;
                        check_a = 0;
		}
	}
}
