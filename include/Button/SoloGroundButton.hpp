//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// GroundButton Class
//

#ifndef SOLOGROUNDBUTTON_HPP_
# define SOLOGROUNDBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class SoloGroundButton : public AButton
{
public:
	SoloGroundButton();
	~SoloGroundButton();

	void	action(Graphics *);
};

#endif /* !SOLOGROUNDBUTTON_HPP_ */
