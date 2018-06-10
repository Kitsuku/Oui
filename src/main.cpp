//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// main menu
//

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include "MainMenu.hpp"
#include "menu.hpp"
#include "Map.hpp"
#include "msleep.h"

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
	AButton *test;

	while (menu && graph.begin()) {
		std::cerr << "Je suis ici" << std::endl;
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph.getController();
		std::cerr << "après get controller" << std::endl;
		ite_button = MoveButtonFromMenu(ite_button, menu, joystickData);
		std::cerr << "après move" << std::endl;
		check = ButtonUnpressed(joystickData, check, 0);
		std::cerr << "après button unpressed" << std::endl;
		menu->displayButton(&graph, ite_button);
		std::cerr << "après display" << std::endl;
		if (check == 2) {
			std::cerr << "dans check" << std::endl;
			menu->getButton(ite_button)->action(&graph);
			std::cerr << "après get button" << std::endl;
			menu = menu->getButton(ite_button)->getBMenu();
			std::cerr << "après getBmenu" << std::endl;
			ite_button = 0;
			check = 0;
		}
		std::cerr << "après check" << std::endl;
		graph.end();
		std::cerr << "après graph end" << std::endl;
	}
	return 0;
}
