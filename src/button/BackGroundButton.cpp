//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// BackGroundButton functions
//

#ifdef WIN32
#include <io.h>
#include <windows.h>
#include "dirent_windows.h"
#else
#include <unistd.h>
#include <dirent.h>
#endif
#include <sys/types.h>
#include <cstdlib>
#include <fstream>
#include "BackGroundButton.hpp"

BackGroundButton::BackGroundButton()
{
	_name = "Background";
}

BackGroundButton::~BackGroundButton()
{
}

std::vector<std::string>	getFilesBackground()
{
	struct dirent	*dirp;
	DIR	*dir;
	std::vector<std::string>	files;
	std::string	path = "./res/Background/";

	dir = opendir("./res/Background");
	dirp = readdir(dir);
	while (dirp) {
		if (dirp->d_name[0] != '.') {
			path.append(dirp->d_name);
			std::cout << path << std::endl;
			files.push_back(path);
			path = "./res/Background/";
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

void	BackGroundButton::action(Graphics *graph)
{
	std::vector<std::string>	file_content;
	std::vector<std::string>	files;
	unsigned int			ite = 0;

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
