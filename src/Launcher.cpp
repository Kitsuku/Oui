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

void	Launcher::launch()
{
	std::unique_ptr<AMenu> main_menu (new MainMenu);
	AMenu		*menu = main_menu.get();
	unsigned int	ite_button = 0;
	Graphics	graph(_path);
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
}