/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** launcher functions
*/

#include "MainMenu.hpp"
#include "menu.hpp"
#include "Map.hpp"
#include "Launcher.hpp"
#include "msleep.h"

Launcher::Launcher()
{
}

Launcher::~Launcher()
{
}

void	Launcher::setPath(const std::string &path)
{
	_path = path;
}

void	Launcher::splashScreen(Graphics *graph)
{
	int	check_start = 0;
	int	flashing = 0;

	while (graph->begin() && check_start != 2) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_start = ButtonUnpressed(joystickData, check_start, 7);
		graph->displayBackground("res/splash.jpg");
		if (flashing >= 0 && flashing <= 40)
			graph->displayText("PRESS START TO CONTINUE",
			{675, 800, 200, 30}, {255, 255, 255, 255});
		flashing += 1;
		if (flashing > 80)
			flashing = 0;
		graph->end();
	}
}

void	Launcher::launch()
{
	std::unique_ptr<AMenu> main_menu (new MainMenu);
	AMenu		*menu = main_menu.get();
	unsigned int	ite_button = 0;
	Graphics	graph(_path);
	int		check = 0;

	this->splashScreen(&graph);
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
}
