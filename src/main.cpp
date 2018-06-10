//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// main menu
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "Launcher.hpp"
#include "MyException.hpp"

int	main(int ac, char **av)
{
	std::string	path(av[0]);
	unsigned int 	size = path.size();
	Launcher	launcher;

	while (path[size] != '/') {
		--size;
	}
	path = path.substr(0, size + 1);
	launcher.setPath(path);
	try {
		launcher.launch();
	} catch (const MyException &error) {
		std::cout << error.what() << std::endl;
		return 84;
	}
	return 0;
}
