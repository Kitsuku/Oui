//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// MultiButton Class
//

#ifndef MULTIBUTTON_HPP_
# define MULTIBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class MultiButton : public AButton
{
public:
	MultiButton();
	~MultiButton();

	void	action(Graphics *);
};

#endif /* !MULTIBUTTON_HPP_ */
