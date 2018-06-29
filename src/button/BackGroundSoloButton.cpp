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

std::vector<std::string>	getFilesBackground(
				const std::string &beginPath)
{
	struct dirent	*dirp;
	DIR	*dir;
	std::vector<std::string>	files;
	const std::string	&endPath = "res/Background/";
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

void	writeBackgroundConf(std::string path, std::vector<std::string> content,
	const std::string &beginConf)
{
	std::ofstream	file;

	file.open((beginConf + "/.conf").c_str(), std::ofstream::trunc | std::ofstream::out);
	file << path << std::endl;
	file << content.at(1) << std::endl;
	file << content.at(2) << std::endl;
	file.close();
}

std::vector<std::string>	getConfBackgroundContent(
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

void	BackGroundSoloButton::action(Graphics *graph)
{
	std::unique_ptr<AMenu>	solo_menu = std::make_unique<SoloMenu>();
	const std::string		&path = graph->getPath();
	std::vector<std::string>	file_content;
	std::vector<std::string>	files;
	unsigned int			ite = 0;

	_menu = std::move(solo_menu);
	file_content = getConfBackgroundContent(path);
	files = getFilesBackground(path);
	while (files.size() > ite && file_content.at(0).compare(files.at(ite)) != 0)
		ite += 1;
	ite += 1;
	if (ite >= files.size())
		ite = 0;
	writeBackgroundConf(files.at(ite), file_content, path);
}
