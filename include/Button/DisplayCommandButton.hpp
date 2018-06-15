//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// DisplayCommandButton class
//

#ifndef DISPLAYCOMMANDBUTTON_HPP_
# define DISPLAYCOMMANDBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class DisplayCommandButton : public AButton
{
public:
	DisplayCommandButton();
	~DisplayCommandButton();

	void	action(Graphics *);
};

#endif /* !DISPLAYCOMMANDBUTTON_HPP_ */
