//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SaveButton class
//

#ifndef SAVEBUTTON_HPP_
# define SAVEBUTTON_HPP_

#include "Map.hpp"
#include "AMenu.hpp"
#include "AButton.hpp"

class SaveButton : public AButton
{
public:
	SaveButton();
	~SaveButton();

	void	action(Graphics *);
	void	save(Map);
};

#endif /* !SAVEBUTTON_HPP_ */
