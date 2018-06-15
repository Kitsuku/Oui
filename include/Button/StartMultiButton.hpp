//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// StartButton
//

#ifndef STARTMULTIBUTTON_HPP_
# define STARTMULTIBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class StartMultiButton : public AButton
{
public:
	StartMultiButton();
	~StartMultiButton();

	void	action(Graphics *);
};

#endif /* !STARTMULTIBUTTON_HPP_ */
