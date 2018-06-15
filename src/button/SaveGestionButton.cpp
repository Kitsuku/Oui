//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SaveGestionButton functions
//

#ifdef WIN32
#include <io.h>
#include "dirent_windows.h"
#else
#include <unistd.h>
#include <dirent.h>
#endif
#include <sys/types.h>
#include <cstdio>
#include "msleep.h"
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

void	displaySaveGestion(Graphics *graph, std::vector<std::string> files, unsigned int ite_file,
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

int     SwitchPageGestion(int ite_file, std::vector<std::string> files, unsigned int page,
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

void	saveGestionSelection(std::vector<std::string> files, Graphics *graph)
{
	unsigned int	ite_file = 0;
	unsigned int	page = 0;
	int		check_a = 0;
	int		check_b = 0;
	std::string	file = "save/";

	while (check_b != 2 && graph->begin()) {
		displaySaveGestion(graph, files, ite_file, page);
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_a = ButtonUnpressed(joystickData, check_a, 0);
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		page = SwitchPageGestion(ite_file, files, page, joystickData);
		ite_file = MoveFileFromMenu(ite_file, files, joystickData);
		if (check_a == 2) {
			file.append(files.at(ite_file));
			remove(file.c_str());
			file = "save/";
			files.erase(files.begin() + ite_file);
		}
		graph->end();
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
