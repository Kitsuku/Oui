//
// EPITECH PROJECT, 2018
// main
// File description:
// main for gene map
//

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "include/ACharacter.hpp"
#include "include/action.hpp"
#include "include/Map.hpp"
#include "include/objects/classUnbrWall.hpp"
#include "include/objects/classWall.hpp"
#include "include/objects/positions.hpp"
#include "include/IA.hpp"
#include "include/Player.hpp"

int	openFieldStartChara(Positions *coord)
{
	if ((coord->y == 0 && coord->x == 10) ||
	    (coord->y == 1 && coord->x == 12) ||
	    (coord->y == 8 && coord->x == 12)) {
		coord->y += 1;
		coord->x = 1;
		return 1;
	}
	if (coord->y == 9 && coord->x == 12) {
		coord->y += 1;
		coord->x = 3;
		return 1;
	}
	if (coord->y == 10 && coord->x == 11) {
		coord->y = 11;
		return 1;
	}
	return 0;
}

void	Map::generateCharacter(int nbPlayer)
{
	Positions	pos;

	if (nbPlayer == 1) {
		pos.x = 0;
		pos.y = 0;
		std::unique_ptr<ACharacter>	newChara(new Player(1, pos));
		this->_characters.push_back(std::move(newChara));
		pos.x = 12;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newIA1(new IA(-1, pos));
		this->_characters.push_back(std::move(newIA1));
		pos.x = 0;
		pos.y = 10;
		std::unique_ptr<ACharacter>     newIA2(new IA(-2, pos));
		this->_characters.push_back(std::move(newIA2));
		pos.x = 12;
		pos.y = 10;
		std::unique_ptr<ACharacter>     newIA3(new IA(-3, pos));
		this->_characters.push_back(std::move(newIA3));
	}
	else if (nbPlayer == 2){
		pos.x =	0;
                pos.y =	0;
                std::unique_ptr<ACharacter>     newChara(new Player(1, pos));
                this->_characters.push_back(std::move(newChara));
                pos.x =	12;
                pos.y =	0;
                std::unique_ptr<ACharacter>     newChara2(new Player(2, pos));
                this->_characters.push_back(std::move(newChara2));
		pos.x =	0;
                pos.y =	10;
                std::unique_ptr<ACharacter>     newIA(new IA(-1, pos));
                this->_characters.push_back(std::move(newIA));
		pos.x =	12;
                pos.y =	10;
                std::unique_ptr<ACharacter>     newIA2(new IA(-2, pos));
                this->_characters.push_back(std::move(newIA2));
	}
}

void	Map::coordForUnbrWall()
{
	Positions		pos;
	std::vector<int>	test;

	for (int y = 1; y < 10; y++) {
		for(int x = 1; x < 12; x += 2) {
			pos.y = y;
			pos.x = x;
			std::cout << "x = " << pos.x << " y = " << pos.y << std::endl;
			std::unique_ptr<AObject>	newWall(new UnbrWall(pos, test));
			this->_map.push_back(std::move(newWall));
		}
	}
}

void	Map::generateMap()
{
	Positions			coord;
	int				rand;
	std::vector<int>		test;

	coord.x = 2;
	coord.y = 0;
	while (coord.y != 11) {
		rand = (1 + std::rand()/((100 + 1u)/6)) % 100;
		openFieldStartChara(&coord);
		if (rand <= 83 && coord.x <= 12 && coord.y <= 10) {
			std::unique_ptr<AObject>	newWall(new Wall(coord, test, test));
			this->_map.push_back(std::move(newWall));
		}
		coord.x += 1;
		if (static_cast<int> (coord.x) % 13 == 0) {
			coord.x = 0;
			coord.y += 1;
		}
	}
}

void	Map::setSpriteGroundAndBackGround()
{
	std::ifstream	fichier(".conf", std::ios::in);
	std::string	test;

        if (fichier) {
		getline(fichier, test);
		this->_backGround = test;
		getline(fichier, test);
		this->_ground = test;
                fichier.close();
        }
        else
		std::cout << "Probleme with configuration." << std::endl;
}

void	Map::setSizeMap(int posX, int posY)
{
	this->_mapSize.x = posX;
	this->_mapSize.y = posY;
}

int	main()
{
	std::cout << "hELELELELL" < std::endl;
/*
	Map	map(1, 1);
	Map	load(1, 1);
	AObject	*obj;
	Positions	objPos;

	std::srand(std::time(nullptr));
	map.setSizeMap(13, 11);
	map.generateMap();
	map.generateCharacter(2);

	std::cout << "Map created :" << std::endl;
	for (int it = 0; it < map.getNbMapElem(); it++) {
		obj = map.getMapElem(it);
		objPos = obj->getPos();
		std::cout << "ObjType = " << obj->getObjectType()
			  << ", pos x = " << objPos.x << " et pos y = " << objPos.y << std::endl;
	}
	map.saveMap();
	

	load.loadMapFromSave("save.json");
	std::cout << "Map loaded: " << std::endl;
	std::cout << load.getNbMapElem() << std::endl;
	for (int it = 0; it < load.getNbMapElem(); it++) {
		obj = load.getMapElem(it);
		objPos = obj->getPos();
		std::cout << "ObjType = " << obj->getObjectType()
			  << ", pos x = " << objPos.x << " et pos y = " << objPos.y << std::endl;
			  }
			  map.setSpriteGroundAndBackGround();*/
	return 0;
}
