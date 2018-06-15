//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// BackGroundButton Class
//

#ifndef BACKGROUNDSOLOBUTTON_HPP_
# define BACKGROUNDSOLOBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class BackGroundSoloButton : public AButton
{
public:
	BackGroundSoloButton();
	~BackGroundSoloButton();

	void	action(Graphics *);
};

#endif /* !BACKGROUNDSOLOBUTTON_HPP_ */
