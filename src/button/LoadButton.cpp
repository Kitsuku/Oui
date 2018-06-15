//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// LoadButton functions
//

#ifdef WIN32
#include <io.h>
#include "dirent_windows.h"
#else
#include <dirent.h>
#include <unistd.h>
#endif
#include <sys/types.h>
#include "msleep.h"
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

void	displayLoad(Graphics *graph, std::vector<std::string> files, unsigned int ite_file,
		    unsigned int page)
{
	unsigned int	ite = 0 + (page * 4);
	float		y = 400;
	color_t		color = {100, 255, 0, 0};

	graph->displayImage("res/Bomberman_artwork.png", {25, 360, 700, 700});
	graph->displayImage("res/Bomberman_Title.png", {300, 25, 1280, 355});
	graph->displayText("PRESS B TO GO BACK ",
			{1550, 1040, 200, 30}, {100, 255, 255, 255});
	graph->displayText("USE JOYSTICK RIGHT OR LEFT TO SWITCH PAGE",
			{650, 1040, 200, 30}, {100, 255, 255, 255});
	while (ite < files.size()) {
		if (ite == (ite_file + (page * 4)))
			graph->displayBox({725, y, 650, 100}, {100, 0, 255, 0});
		else
			graph->displayBox({725, y, 650, 100}, color);
		graph->displayText(files.at(ite), {750, y, 300, 50},
				   {100, 255, 255, 255});
		y += 175;
		ite += 1;
	}
}

int	SwitchPageLoad(int ite_file, std::vector<std::string> files, unsigned int page,
		       std::vector<irr::SEvent::SJoystickEvent> joystickData)
{
	if (joystickData[0].Axis[irr::SEvent::SJoystickEvent::AXIS_X] < -10000
	&& page > 0) {
		page -= 1;
		msleep(500);
	} else if (joystickData[0].Axis[irr::SEvent::SJoystickEvent::AXIS_X] > 10000
		&& (page * 4) <  files.size()) {
		page += 1;
		msleep(500);
	}
	return page;
}

void	loadButtonSelection(std::vector<std::string> files, Graphics *graph)
{
	unsigned int	ite_file = 0;
	int	check_a = 0;
	int	check_b = 0;
	unsigned int	page = 0;
	Map	map(1, 1);
	std::string	path = "./save/";

	while(check_a != 2 && graph->begin()) {
		displayLoad(graph, files, ite_file, page);
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		page = SwitchPageLoad(ite_file, files, page, joystickData);
		ite_file = MoveFileFromMenu(ite_file, files, joystickData);
		if (check_b == 2)
			return;
		graph->end();
	}
	map.loadMapFromSave(path + files.at(ite_file));	
	map.play(graph);
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
