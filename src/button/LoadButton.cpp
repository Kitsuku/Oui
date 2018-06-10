//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// LoadButton functions
//

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
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

void	displayLoad(Graphics *graph, std::vector<std::string> files, unsigned int ite_file)
{
	unsigned int	ite = 0;
	float		y = 400;
	color_t		color = {100, 255, 0, 0};

	graph->displayImage("res/Bomberman_artwork.png", {25, 360, 700, 700});
	graph->displayImage("res/Bomberman_Title.png", {300, 25, 1280, 355});
	graph->displayText("PRESS B TO GO BACK ",
			   {1500, 1020, 200, 30}, {100, 255, 255, 255});
	while (ite < files.size()) {
		if (ite == ite_file)
			graph->displayBox({750, y, 500, 100}, {100, 0, 255, 0});
		else
			graph->displayBox({750, y, 500, 100}, color);
		graph->displayText(files.at(ite), {950, y, 300, 50},
				   {100, 255, 255, 255});
		y += 175;
		ite += 1;
	}
}

void	loadButtonSelection(std::vector<std::string> files, Graphics *graph)
{
	unsigned int	ite_file = 0;
	int	check_a = 0;
	int	check_b = 0;
	Map	map(1, 1);

	while(check_a != 2 && graph->begin()) {
		displayLoad(graph, files, ite_file);
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		ite_file = MoveFileFromMenu(ite_file, files, joystickData);
		if (check_b == 2)
			return;
		graph->end();
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

	graph = graph;
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
