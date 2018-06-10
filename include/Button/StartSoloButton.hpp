//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// StartButton
//

#ifndef STARTSOLOBUTTON_HPP_
# define STARTSOLOBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class StartSoloButton : public AButton
{
public:
	StartSoloButton();
	~StartSoloButton();

	void	action(Graphics *);
};

#endif /* !STARTSOLOBUTTON_HPP_ */
