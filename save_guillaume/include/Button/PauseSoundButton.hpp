//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// PauseSoundButton class
//

#ifndef PAUSESOUNDBUTTON_HPP_
# define PAUSESOUNDBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class PauseSoundButton : public AButton
{
public:
	PauseSoundButton();
	~PauseSoundButton();

	void	action(Graphics *);
};

#endif /* !PAUSESOUNDBUTTON_HPP_ */
