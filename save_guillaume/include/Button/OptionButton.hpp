//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// OptinButton class
//

#ifndef OPTIONBUTTON_HPP_
# define OPTIONBUTTON_HPP_

#include "AButton.hpp"
#include "AMenu.hpp"

class OptionButton : public AButton
{
public:
	OptionButton();
	~OptionButton();

	void	action(Graphics *);
};

#endif /* !OPTIONBUTTON_HPP_  */
