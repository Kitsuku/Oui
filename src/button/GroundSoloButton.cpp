//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// GroundButton functions
//

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include "SoloMenu.hpp"
#include "SoloGroundButton.hpp"

SoloGroundButton::SoloGroundButton()
{
	_name = "Ground";
}

SoloGroundButton::~SoloGroundButton()
{
}

std::vector<std::string>	getFilesGround()
{
	struct dirent			*dirp;
	DIR				*dir;
	std::vector<std::string>	files;
	std::string	path = "res/Ground/";

	dir = opendir("res/Ground");
	dirp = readdir(dir);
	while (dirp) {
		if (dirp->d_name[0] != '.') {
			path.append(dirp->d_name);
			files.push_back(path);
			path = "res/Ground/";
		}
		dirp = readdir(dir);
	}
	closedir(dir);
	return files;
}

void	writeGroundConf(std::string path, std::vector<std::string> content)
{
	std::ofstream			file;

	file.open(".conf", std::ofstream::trunc | std::ofstream::out);
	file << content.at(0) << std::endl;
	file << path << std::endl;
	file << content.at(2) << std::endl;
	file.close();
}

std::vector<std::string>	getConfGroundContent()
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

void	SoloGroundButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu>	solo_menu (new SoloMenu);
	std::vector<std::string>	file_content;
	std::vector<std::string>	files;
	unsigned int			ite = 0;

	_menu = std::move(solo_menu);
	graph = graph;
	file_content = getConfGroundContent();
	files = getFilesGround();
	while (files.size() > ite && file_content.at(1).compare(files.at(ite)) != 0)
		ite += 1;
	ite += 1;
	if (ite >= files.size())
		ite = 0;
	writeGroundConf(files.at(ite), file_content);
}
