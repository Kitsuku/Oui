//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// Fct Gestion
//

#ifdef WIN32
#include <io.h>
#define VALUE_MSLEEP 500
#else
#include <unistd.h>
#define VALUE_MSLEEP 500
#endif
#include "msleep.h"
#include "AMenu.hpp"
#include "Graphics.hpp"

int	ButtonUnpressed(std::vector<irr::SEvent::SJoystickEvent> joystickData, int check, int button)
{
	if (joystickData[0].IsButtonPressed(button) == 1)
		return 1;
	else if (joystickData[0].IsButtonPressed(button) == 0 && check == 1)
		return 2;
	return 0;
}

unsigned int	ChangeSoundMenu(unsigned int ite_sound,
				std::vector<irr::SEvent::SJoystickEvent> joystickData)
{
	if (joystickData[0].Axis[irr::SEvent::SJoystickEvent::AXIS_Y] < -10000
	    && ite_sound < 10) {
		ite_sound += 1;
		msleep(VALUE_MSLEEP);
	} else if (joystickData[0].Axis[irr::SEvent::SJoystickEvent::AXIS_Y] > 10000
		&& ite_sound > 0) {
		ite_sound -= 1;
		msleep(VALUE_MSLEEP);
	}
	return ite_sound;
}

unsigned int	MoveButtonFromMenu(unsigned int ite_button, AMenu *menu,
                                   std::vector<irr::SEvent::SJoystickEvent> joystickData)
{
	if (joystickData[0].Axis[irr::SEvent::SJoystickEvent::AXIS_Y] < -10000
	    && ite_button > 0) {
		ite_button -= 1;
		msleep(VALUE_MSLEEP);
	} else if (joystickData[0].Axis[irr::SEvent::SJoystickEvent::AXIS_Y] > 10000
		&& ite_button < menu->getNbButton()) {
		ite_button += 1;
		msleep(VALUE_MSLEEP);
	}
	return ite_button;
}

unsigned int	MoveFileFromMenu(unsigned int ite_file,
                                std::vector<std::string> files,
                                std::vector<irr::SEvent::SJoystickEvent> joystickData)
{
	if (joystickData[0].Axis[irr::SEvent::SJoystickEvent::AXIS_Y] < -10000
	&& ite_file > 0) {
		ite_file -= 1;
		msleep(VALUE_MSLEEP);
	} else if (joystickData[0].Axis[irr::SEvent::SJoystickEvent::AXIS_Y] > 10000
		   && ite_file < (files.size() - 1)) {
		ite_file += 1;
		msleep(VALUE_MSLEEP);
	}
	return ite_file;
}
