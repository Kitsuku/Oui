//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// BackGroundButton functions
//

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include "SoloMenu.hpp"
#include "BackGroundSoloButton.hpp"

BackGroundSoloButton::BackGroundSoloButton()
{
	_name = "Background";
}

BackGroundSoloButton::~BackGroundSoloButton()
{
}

std::vector<std::string>	getFilesBackground()
{
	struct dirent	*dirp;
	DIR	*dir;
	std::vector<std::string>	files;
	std::string	path = "res/Background/";

	dir = opendir("res/Background");
	dirp = readdir(dir);
	while (dirp) {
		if (dirp->d_name[0] != '.') {
			path.append(dirp->d_name);
			files.push_back(path);
			path = "res/Background/";
		}
		dirp = readdir(dir);
	}
	closedir(dir);
	return files;
}

void	writeBackgroundConf(std::string path, std::vector<std::string> content)
{
	std::ofstream	file;

	file.open(".conf", std::ofstream::trunc | std::ofstream::out);
	file << path << std::endl;
	file << content.at(1) << std::endl;
	file << content.at(2) << std::endl;
	file.close();
}

std::vector<std::string>	getConfBackgroundContent()
{
	std::string	line;
	std::ifstream	file;
	std::vector<std::string>	file_content;

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

void	BackGroundSoloButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu>	solo_menu (new SoloMenu);
	std::vector<std::string>	file_content;
	std::vector<std::string>	files;
	unsigned int			ite = 0;

	_menu = std::move(solo_menu);
	graph = graph;
	file_content = getConfBackgroundContent();
	files = getFilesBackground();
	while (files.size() > ite && file_content.at(0).compare(files.at(ite)) != 0)
		ite += 1;
	ite += 1;
	if (ite >= files.size())
		ite = 0;
	writeBackgroundConf(files.at(ite), file_content);
}
