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
#include "MultiGroundButton.hpp"
#include "MultiMenu.hpp"

MultiGroundButton::MultiGroundButton()
{
	_name = "Ground";
}

MultiGroundButton::~MultiGroundButton()
{
}

std::vector<std::string>	getFilesGroundMulti(
				const std::string &beginPath)
{
	struct dirent			*dirp;
	DIR				*dir;
	std::vector<std::string>	files;
	const std::string	&endPath = "res/Ground/";
	const std::string	&path = beginPath + endPath;

	dir = opendir(path.c_str());
	dirp = readdir(dir);
	while (dirp) {
		if (dirp->d_name[0] != '.') {
			files.push_back(endPath + dirp->d_name);
		}
		dirp = readdir(dir);
	}
	closedir(dir);
	return files;
}

void	writeGroundMultiConf(std::string path, std::vector<std::string> content,
	const std::string &beginConf)
{
	std::ofstream			file;

	file.open((beginConf + "/.conf").c_str(), std::ofstream::trunc | std::ofstream::out);
	file << content.at(0) << std::endl;
	file << path << std::endl;
	file << content.at(2) << std::endl;
	file.close();
}

std::vector<std::string>	getConfGroundMultiContent(
				const std::string &path)
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

void	MultiGroundButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu>	multi_menu = std::make_unique<MultiMenu>();
	const std::string		&path = graph->getPath();
	std::vector<std::string>	file_content;
	std::vector<std::string>	files;
	unsigned int			ite = 0;

	_menu = std::move(multi_menu);
	file_content = getConfGroundMultiContent(path);
	files = getFilesGroundMulti(path);
	while (files.size() > ite && file_content.at(1).compare(files.at(ite)) != 0)
		ite += 1;
	ite += 1;
	if (ite >= files.size())
		ite = 0;
	writeGroundMultiConf(files.at(ite), file_content, path);
}
