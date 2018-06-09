//
// EPITECH PROJECT, 2018
// IndieStudio
// File description:
// LoadButton Class
//

#ifndef LOADBUTTON_HPP_
# define LOADBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class LoadButton : public AButton
{
public:
	LoadButton();
	~LoadButton();

	void	action(Graphics *);
};

#endif /* !LOADBUTTON_HPP_ */
