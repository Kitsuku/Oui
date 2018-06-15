//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// GroundButton Class
//

#ifndef MULTIGROUNDBUTTON_HPP_
# define MULTIGROUNDBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class MultiGroundButton : public AButton
{
public:
	MultiGroundButton();
	~MultiGroundButton();

	void	action(Graphics *);
};

#endif /* !MULTIGROUNDBUTTON_HPP_ */
