//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SaveGestionButton functions
//

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <sys/types.h>
#include <dirent.h>
#include <cstdio>
#include "SaveGestionButton.hpp"
#include "OptionMenu.hpp"
#include "menu.hpp"

SaveGestionButton::SaveGestionButton()
{
	_name = "Save";
}

SaveGestionButton::~SaveGestionButton()
{
}

void	saveGestionSelection(std::vector<std::string> files, Graphics *graph)
{
	unsigned int	ite_file = 0;
	int		check_a = 0;
	int		check_b = 0;
	std::string	file = "save/";

	while (check_b != 2 && graph->run()) {
		std::cout << std::endl;
		for (unsigned int ite = 0; ite < files.size(); ite += 1)
			std::cout << files.at(ite) << std::endl; //Bonne fct + change color pour
								 //ite = ite_file
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		std::cout << check_a << std::endl;
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		ite_file = MoveFileFromMenu(ite_file, files, joystickData);
		if (check_a == 2) {
			file.append(files.at(ite_file));
			remove(file.c_str());
			file = "save/";
			files.erase(files.begin() + ite_file);
		}
	}
}

void	SaveGestionButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> option (new OptionMenu);
	struct dirent	*dirp;
	std::vector<std::string> files;
	DIR	*dir;

	_menu = std::move(option);
	dir = opendir("save");
	if (!dir)
		return;
	dirp = readdir(dir);
	while (dirp) {
		if (dirp->d_name[0] != '.')
		files.push_back(dirp->d_name);
		dirp = readdir(dir);
	}
	saveGestionSelection(files, graph);
	closedir(dir);
}
