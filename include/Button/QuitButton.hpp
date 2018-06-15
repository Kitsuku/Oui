//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// QuitButton Class
//

#ifndef QUUITBUTTON_HPP_
# define QUUITBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class QuitButton : public AButton
{
public:
	QuitButton();
	~QuitButton();

	void	action(Graphics *);
};

#endif /* !QUUITBUTTON_HPP_ */
