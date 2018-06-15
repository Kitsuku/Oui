//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// ExitButton class
//

#ifndef EXITBUTTON_HPP_
# define EXITBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class ExitButton : public AButton
{
public:
	ExitButton();
	~ExitButton();

	void	action(Graphics *);
};

#endif /* !EXITBUTTON_HPP_ */
