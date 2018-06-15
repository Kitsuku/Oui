//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// main menu
//

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include "Launcher.hpp"
#include "MyException.hpp"
#include "msleep.h"

int	main(int ac, char **av)
{
	std::string	path(av[0]);
	unsigned int 	size = path.size();
	Launcher	launcher;

#ifdef WIN32
	while (path[size] != '\\') {
		--size;
	}
	path = path.substr(0, size);
	path += "/";
#else
	while (path[size] != '/') {
		--size;
	}
	path = path.substr(0, size + 1);
#endif
	launcher.setPath(path);
	try {
		launcher.launch();
	} catch (const MyException &error) {
		std::cout << error.what() << std::endl;
		return 84;
	}
	return 0;
}
