//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// BackGroundButton Class
//

#ifndef BACKGROUNDBUTTON_HPP_
# define BACKGROUNDBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class BackGroundButton : public AButton
{
public:
	BackGroundButton();
	~BackGroundButton();

	void	action(Graphics *);
};

#endif /* !BACKGROUNDBUTTON_HPP_ */
