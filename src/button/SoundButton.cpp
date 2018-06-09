//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SoundButton functions
//

#include "SoundButton.hpp"
#include "OptionMenu.hpp"
#include "menu.hpp"

SoundButton::SoundButton()
{
	_name = "Sound";
}

SoundButton::~SoundButton()
{
}

void	SoundButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> option (new OptionMenu);
	int	check_b = 0;
	unsigned int	ite_sound = 5;

	_menu = std::move(option);
	while (check_b != 2 && graph->run()) {
		const std::vector<irr::SEvent::SJoystickEvent>
                        &joystickData = graph->getController();
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		ite_sound = ChangeSoundMenu(ite_sound, joystickData);
	}
}
