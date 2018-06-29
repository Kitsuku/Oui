//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// AMenu Functions
//

#include <iostream>
#include "AMenu.hpp"
#include "AButton.hpp"

void		AMenu::displayButtonBox(Graphics *graph, int ite_button, unsigned int size)
{
	unsigned int	ite = 0;
	rect_t	box = {750, 400, 500, 100};
	color_t	color = {100, 255, 0, 0};

	while (ite < size) {
		if (ite == ite_button) {
			color.green = 255;
			color.red = 0;
		}
		graph->displayBox(box, color);
		box.posY += 175;
		if (ite == ite_button) {
			color.green = 0;
			color.red = 255;
		}
		ite += 1;
	}

}

void		AMenu::displayButtonName(Graphics *graph, unsigned int size)
{
	unsigned int	ite = 0;
	rect_t	coord = {950, 425, 300, 50};
	color_t	color = {255, 255, 255, 255};

	while (ite < size) {
	graph->displayText(this->getButton(ite)->getName(), coord, color);
		coord.posY += 175;
		ite += 1;
	}
}

void		AMenu::displayButton(Graphics *graph, int size)
{
	graph->displayImage("res/Bomberman_artwork.png", {25, 360, 700, 700});
	graph->displayImage("res/Bomberman_Title.png", {300, 25, 1280, 355});
	this->affButton(graph, size);
}

int		AMenu::affButton(Graphics *graph, int ite_button)
{
	this->displayButtonBox(graph, ite_button, _buttons.size());
	this->displayButtonName(graph, _buttons.size());
	return 0;
}

AButton		*AMenu::getButton(int pos)
{
	return _buttons.at(pos).get();
}

unsigned int	AMenu::getNbButton()
{
	return _buttons.size() - 1;
}

std::string	AMenu::getName()
{
	return _name;
}
