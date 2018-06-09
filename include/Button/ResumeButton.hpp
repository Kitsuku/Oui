//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// ResumeButton
//

#ifndef RESUMEBUTTON_HPP_
# define RESUMEBUTTON_HPP_

#include "AMenu.hpp"
#include "AButton.hpp"

class ResumeButton : public AButton
{
public:
	ResumeButton();
	~ResumeButton();

	void	action(Graphics *);
};

#endif /* !RESUMEBUTTON_HPP_ */
