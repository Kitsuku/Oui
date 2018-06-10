//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// BackGroundButton Class
//

#ifndef BACKGROUNDMULTIBUTTON_HPP_
# define BACKGROUNDMULTIBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class BackGroundMultiButton : public AButton
{
public:
	BackGroundMultiButton();
	~BackGroundMultiButton();

	void	action(Graphics *);
};

#endif /* !BACKGROUNDMULTIBUTTON_HPP_ */
