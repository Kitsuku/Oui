//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SaveButton functions
//

#ifdef WIN32
#include "dirent_windows.h"
#else
#include <dirent.h>
#endif
#include <sys/types.h>
#include <ctime>
#include "Map.hpp"
#include "SaveButton.hpp"
#include "PauseMenu.hpp"

SaveButton::SaveButton()
{
	_name = "Save";
}

SaveButton::~SaveButton()
{
}

void	SaveButton::save(Map map)
{
	std::unique_ptr<AMenu>	pause (new PauseMenu);
	time_t			now = time(0);
	std::string		actual_time = ctime(&now);
	std::string		path;
	size_t			ite = 0;

	_menu = std::move(pause);
	if (map.getNbCharacter() == 1)
		path = "solo_";
	else
		path = "mutli_";
	actual_time = actual_time.substr(0, actual_time.size() - 1);
	path.append(actual_time);
	ite = path.find(':', ite);
	while (ite != std::string::npos) {
		path.at(ite) = '_';
		ite = path.find(':', ite);
	}
	path.append(".json");
	map.saveMap(path);
}

void	SaveButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu>	pause (new PauseMenu);

	_menu = std::move(pause);
	graph = graph;
}
