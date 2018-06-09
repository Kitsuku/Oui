//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// StartButton
//

#ifndef STARTBUTTON_HPP_
# define STARTBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class StartButton : public AButton
{
public:
	StartButton();
	~StartButton();

	void	action(Graphics *);
};

#endif /* !STARTBUTTON_HPP_ */
