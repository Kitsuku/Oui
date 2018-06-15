//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// main gestion menu
//

#ifndef GESTIONMENU_HPP_
# define GESTIONMENU_HPP_

#include "AMenu.hpp"
#include "Graphics.hpp"

int		ButtonUnpressed(std::vector<irr::SEvent::SJoystickEvent>, int, int);
unsigned int	ChangeSoundMenu(unsigned int, std::vector<irr::SEvent::SJoystickEvent>);
unsigned int	MoveButtonFromMenu(unsigned int, AMenu *, std::vector<irr::SEvent::SJoystickEvent>);
unsigned int	MoveFileFromMenu(unsigned int, std::vector<std::string>,
				 std::vector<irr::SEvent::SJoystickEvent>);

#endif /* !GESTIONMENU_HPP_ */
