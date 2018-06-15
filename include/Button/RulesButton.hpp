//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// RulesButton Class
//

#ifndef RULESBUTTON_HPP_
# define RULESBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class RulesButton : public AButton
{
public:
	RulesButton();
	~RulesButton();

	void	action(Graphics *);
};

#endif /* !RULESBUTTON_HPP_ */
