//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// PauseSoundButton functions
//

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include "PauseSoundButton.hpp"
#include "PauseMenu.hpp"
#include "menu.hpp"

PauseSoundButton::PauseSoundButton()
{
	_name = "Sound";
}

PauseSoundButton::~PauseSoundButton()
{
}

std::vector<std::string>        getConfSoundPauseContent()
{
	std::string	line;
	std::ifstream	file;
	std::vector<std::string>        file_content;

	file.open(".conf", std::ifstream::in);
	if (file.is_open()) {
		getline(file, line);
		file_content.push_back(line);
		getline(file, line);
		file_content.push_back(line);
		getline(file, line);
		file_content.push_back(line);
	}
	file.close();
	return (file_content);
}

void    writeSoundPauseMenuConf(int ite_sound, std::vector<std::string> content)
{
	std::ofstream	file;

	file.open(".conf", std::ofstream::trunc | std::ofstream::out);
	file << content.at(0) << std::endl;
	file << content.at(1) << std::endl;
	file << ite_sound << std::endl;
	file.close();
}

void	displaySoundPauseInterface(Graphics *graph, int ite_sound)
{
	graph->displayImage("res/Bomberman_artwork.png", {25, 360, 700, 700});
	graph->displayImage("res/Bomberman_Title.png", {300, 25, 1280, 355});
	graph->displayBox({890, 400, 200, 600}, {100, 0, 255, 0});
	graph->displayBox({890, 400, 200, (60 * (10 - ite_sound))}, {100, 0, 0, 0});
	graph->displayBox({890, 400, 200, (60 * (10 - ite_sound))}, {100, 0, 0, 255});
	graph->displayText("VOLUME: ", {890, 1020, 200, 30}, {100, 255, 255, 255});
	graph->displayText(std::to_string(ite_sound), {1050, 1020, 200, 30}, {100, 255, 255, 255});
	graph->displayText("PRESS B TO GO BACK ", {1500, 1020, 200, 30}, {100, 255, 255, 255});
}

unsigned int    getSoundConfPause()
{
	std::string	line;
	std::ifstream	file;
	unsigned int	sound;

	file.open(".conf", std::ifstream::in);
	if (file.is_open()) {
		getline(file, line);
		getline(file, line);
		getline(file, line);
	}
	file.close();
	sound =	std::stoi(line, 0, 10);
	return (sound);
}

void	PauseSoundButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> pause (new PauseMenu);
	int	check_b = 0;
	unsigned int	ite_sound = getSoundConfPause();
	std::vector<std::string>	file_content;

	_menu = std::move(pause);
	while (check_b != 2 && graph->begin()) {
		const std::vector<irr::SEvent::SJoystickEvent>
			&joystickData = graph->getController();
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		ite_sound = ChangeSoundMenu(ite_sound, joystickData);
		file_content = getConfSoundPauseContent();
		writeSoundPauseMenuConf(ite_sound, file_content);
		displaySoundPauseInterface(graph, ite_sound);
		graph->end();
	}
}
