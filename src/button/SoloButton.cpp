//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SoloButton functions
//

#include "SoloButton.hpp"
#include "SoloMenu.hpp"

SoloButton::SoloButton()
{
	_name = "Solo";
}

SoloButton::~SoloButton()
{
}

void	SoloButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> solo = std::make_unique<SoloMenu>();

	_menu = std::move(solo);
	graph = graph;
}
