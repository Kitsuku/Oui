//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// PauseSoundButton functions
//

#include "PauseSoundButton.hpp"
#include "PauseMenu.hpp"
#include "menu.hpp"

PauseSoundButton::PauseSoundButton()
{
	_name = "Sound";
}

PauseSoundButton::~PauseSoundButton()
{
}

void	PauseSoundButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> pause (new PauseMenu);
	int	check_b = 0;
	unsigned int	ite_sound = 5;

	_menu = std::move(pause);
	while (check_b != 2 && graph->run()) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		ite_sound = ChangeSoundMenu(ite_sound, joystickData);
	}
}
