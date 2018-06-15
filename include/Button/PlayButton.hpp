//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// PlayButton class
//

#ifndef PLAYBUTTON_HPP_
# define PLAYBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class PlayButton : public AButton
{
public:
	PlayButton();
	~PlayButton();

	void	action(Graphics *);
};

#endif /* !PLAYBUTTON_HPP_ */
