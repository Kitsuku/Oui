/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** launcher functions
*/

#ifndef LAUNCHER_HPP_
#define LAUNCHER_HPP_

#include <string>
#include "Graphics.hpp"

class Launcher {
public:
	Launcher();
	~Launcher();
	void	setPath(const std::string &path);
	void	launch();
	void	splashScreen(Graphics *);
private:
	std::string	_path;
};

#endif /* !LAUNCHER_HPP_ */
