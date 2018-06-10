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
#include "MultiMenu.hpp"
#include "BackGroundMultiButton.hpp"

BackGroundMultiButton::BackGroundMultiButton()
{
	_name = "Background";
}

BackGroundMultiButton::~BackGroundMultiButton()
{
}

std::vector<std::string>	getFilesBackgroundMulti()
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

void	writeBackgroundMultiConf(std::string path, std::vector<std::string> content)
{
	std::ofstream	file;

	file.open(".conf", std::ofstream::trunc | std::ofstream::out);
	file << path << std::endl;
	file << content.at(1) << std::endl;
	file << content.at(2) << std::endl;
	file.close();
}

std::vector<std::string>	getConfBackgroundMultiContent()
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

void	BackGroundMultiButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu>	multi_menu (new MultiMenu);
	std::vector<std::string>	file_content;
	std::vector<std::string>	files;
	unsigned int			ite = 0;

	graph = graph;
	_menu = std::move(multi_menu);
	file_content = getConfBackgroundMultiContent();
	files = getFilesBackgroundMulti();
	while (files.size() > ite && file_content.at(0).compare(files.at(ite)) != 0)
		ite += 1;
	ite += 1;
	if (ite >= files.size())
		ite = 0;
	writeBackgroundMultiConf(files.at(ite), file_content);
}
