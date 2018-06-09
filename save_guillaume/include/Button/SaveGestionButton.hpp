//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SaveGestionButton Class
//

#ifndef SAVEGESTIONBUTTON_HPP_
# define SAVEGESTIONBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class SaveGestionButton : public AButton
{
public:
	SaveGestionButton();
	~SaveGestionButton();

	void	action(Graphics *);
};

#endif /* !SAVEGESTIONBUTTON_HPP_ */
