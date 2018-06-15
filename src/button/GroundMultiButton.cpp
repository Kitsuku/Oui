//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// GroundButton functions
//

#ifdef WIN32
#include <io.h>
#include "dirent_windows.h"
#else
#include <dirent.h>
#include <unistd.h>
#endif
#include <sys/types.h>
#include <cstdlib>
#include <fstream>
#include "MultiGroundButton.hpp"
#include "MultiMenu.hpp"

MultiGroundButton::MultiGroundButton()
{
	_name = "Ground";
}

MultiGroundButton::~MultiGroundButton()
{
}

std::vector<std::string>	getFilesGroundMulti()
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

void	writeGroundMultiConf(std::string path, std::vector<std::string> content)
{
	std::ofstream			file;

	file.open(".conf", std::ofstream::trunc | std::ofstream::out);
	file << content.at(0) << std::endl;
	file << path << std::endl;
	file << content.at(2) << std::endl;
	file.close();
}

std::vector<std::string>	getConfGroundMultiContent()
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

void	MultiGroundButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu>	multi_menu(new MultiMenu);
	std::vector<std::string>	file_content;
	std::vector<std::string>	files;
	unsigned int			ite = 0;

	_menu = std::move(multi_menu);
	graph = graph;
	file_content = getConfGroundMultiContent();
	files = getFilesGroundMulti();
	while (files.size() > ite && file_content.at(1).compare(files.at(ite)) != 0)
		ite += 1;
	ite += 1;
	if (ite >= files.size())
		ite = 0;
	writeGroundMultiConf(files.at(ite), file_content);
}
