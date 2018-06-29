//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// SoundButton functions
//

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include "SoundButton.hpp"
#include "OptionMenu.hpp"
#include "menu.hpp"

SoundButton::SoundButton()
{
	_name = "Sound";
}

SoundButton::~SoundButton()
{
}

std::vector<std::string>	getConfSoundContent(const std::string &path)
{
	std::string	line;
	std::ifstream	file;
	std::vector<std::string>	file_content;

	file.open((path + "/.conf").c_str(), std::ifstream::in);
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

unsigned int	getSoundConf(const std::string &path)
{
	std::string	line;
	std::ifstream	file;
	unsigned int	sound;

	file.open((path + "/.conf").c_str(), std::ifstream::in);
	if (file.is_open()) {
		getline(file, line);
		getline(file, line);
		getline(file, line);
	}
	file.close();
	sound = std::stoi(line, 0, 10);
	return (sound);
}

void	writeSoundMenuConf(int ite_sound, std::vector<std::string> content,
	const std::string &path)
{
	std::ofstream	file;

	file.open((path + "/.conf").c_str(), std::ofstream::trunc | std::ofstream::out);
	file << content.at(0) << std::endl;
	file << content.at(1) << std::endl;
	file << ite_sound << std::endl;
	file.close();
}

void	displaySoundInterface(Graphics *graph, int ite_sound)
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

void	SoundButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu> option = std::make_unique<OptionMenu>();
	int	check_b = 0;
	const	std::string path = graph->getPath();
	unsigned int	ite_sound = getSoundConf(path);
	std::vector<std::string>	file_content;

	_menu = std::move(option);
	while (check_b != 2 && graph->begin()) {
		const std::vector<irr::SEvent::SJoystickEvent>
                        &joystickData = graph->getController();
		check_b = ButtonUnpressed(joystickData, check_b, 1);
		ite_sound = ChangeSoundMenu(ite_sound, joystickData);
		file_content = getConfSoundContent(path);
		writeSoundMenuConf(ite_sound, file_content, path);
		displaySoundInterface(graph, ite_sound);
		graph->end();
	}
}
