//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// Solo Button class
//

#ifndef SOLOBUTTON_HPP_
# define SOLOBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class SoloButton : public AButton
{
public:
	SoloButton();
	~SoloButton();

	void	action(Graphics *);
};

#endif /* !SOLOBUTTON_HPP_ */
