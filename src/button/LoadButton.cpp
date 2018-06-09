//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// LoadButton functions
//

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <sys/types.h>
#include <dirent.h>
#include "Map.hpp"
#include "LoadButton.hpp"
#include "PlayMenu.hpp"
#include "menu.hpp"

LoadButton::LoadButton()
{
	_name = "Load";
}

LoadButton::~LoadButton()
{
}

void	loadButtonSelection(std::vector<std::string> files, Graphics *graph)
{
	unsigned int	ite_file = 0;
	int	check_a = 0;
	int	check_b = 0;
	Map	map(1, 1);

	while(check_a != 2 && graph->run()) {
		for (unsigned int ite = 0; ite < files.size(); ite += 1)
			std::cout << files.at(ite) << std::endl; //Bonne fct + change color pour
								 //ite = ite_file
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		ite_file = MoveFileFromMenu(ite_file, files, joystickData);
		if (check_b == 2)
			return;
	}
	map.loadMapFromSave(files.at(ite_file));
	//map.play();
}

void	LoadButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> play_menu (new PlayMenu);
	struct dirent	*dirp;
	std::vector<std::string>	files;
	DIR	*dir;

	_menu = std::move(play_menu);
	dir = opendir("save");
	if (!dir)
		return;
	dirp = readdir(dir);
	while (dirp) {
		if (dirp->d_name[0] != '.')
			files.push_back(dirp->d_name);
		dirp = readdir(dir);
	}
	loadButtonSelection(files, graph);
	closedir(dir);
}
