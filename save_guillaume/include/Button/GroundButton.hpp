//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// GroundButton Class
//

#ifndef GROUNDBUTTON_HPP_
# define GROUNDBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class GroundButton : public AButton
{
public:
	GroundButton();
	~GroundButton();

	void	action(Graphics *);
};

#endif /* !GROUNDBUTTON_HPP_ */
