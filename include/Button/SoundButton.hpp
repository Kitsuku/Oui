//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SonButton class
//

#ifndef SOUNDBUTTON_HPP_
# define SOUNDBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class SoundButton : public AButton
{
public:
	SoundButton();
	~SoundButton();

	void	action(Graphics *);
};

#endif /* !SOUNDBUTTON_HPP_ */
