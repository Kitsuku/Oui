//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// ReturnMmButton.hpp
//

#ifndef RETURNMMBUTTON_HPP_
# define RETURNMMBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class ReturnMmButton : public AButton
{
public:
	ReturnMmButton();
	~ReturnMmButton();

	void	action(Graphics *);
};

#endif /* !RETURNMMBUTTON_HPP_ */
