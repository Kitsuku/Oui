//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// main menu
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "MainMenu.hpp"
#include "menu.hpp"
#include "Map.hpp"

/*int	main()
{
	Map	save(1,1);

	std::srand(std::time(nullptr));
	save.setSizeMap(13, 11);
	save.generateMap();
	save.generateCharacter(2);
	save.saveMap();
	return 0;
	}*/

int	main()
{
	std::unique_ptr<AMenu> main_menu (new MainMenu);
	AMenu		*menu = main_menu.get();
	unsigned int	ite_button = 0;
	Graphics	graph("./");
	int		check = 0;

	while (menu && graph.begin()) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph.getController();
		ite_button = MoveButtonFromMenu(ite_button, menu, joystickData);
		check = ButtonUnpressed(joystickData, check, 0);
		menu->displayButton(&graph, ite_button);
		if (check == 2) {
			menu->getButton(ite_button)->action(&graph);
			menu = menu->getButton(ite_button)->getBMenu();
			ite_button = 0;
			check = 0;
		}
		graph.end();
	}
	return 0;
}
