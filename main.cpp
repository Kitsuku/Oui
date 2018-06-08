//
// EPITECH PROJECT, 2018
<<<<<<< HEAD
//
// File description:
//
//

#include <unistd.h>
#include <iostream>
#include <iomanip>
#include "classBomb.hpp"
#include "classWall.hpp"
#include "AObject.hpp"
#include "ACharacter.hpp"

int	drop_bomb(Positions bomb_pos, Positions wall_pos, Positions side_wall_pos, std::vector<int> sprites)
{
	std::unique_ptr<AObject>	my_bomb1(new Bomb(3, bomb_pos, sprites, sprites));
	//std::unique_ptr<AObject>	my_bomb2(new Bomb(3, pos, sprites, sprites));
	std::vector<std::unique_ptr<AObject>>	objects;
	Wall	*my_wall1(new Wall(wall_pos, sprites, sprites));
	Wall	*my_wall2(new Wall(side_wall_pos, sprites, sprites));

	objects.push_back(std::move(my_bomb1));
	//objects.push_back(std::move(my_bomb2));
	for (auto object_it = objects.begin(); object_it != objects.end(); object_it++) {
		((Bomb *)((*object_it).get()))->checkTime();
		((Bomb *)((*object_it).get()))->updateTimer(objects[0].get());
		((Bomb *)((*object_it).get()))->updatePower((AObject *)my_wall2);
		std::cout << "Entering checkBreak wall1" << std::endl;
		my_wall1->checkBreak((*object_it).get());
		std::cout << "Entering checkBreak wall2" << std::endl;
		my_wall2->checkBreak((*object_it).get());
	}
	sleep(3);
	for (auto object_it = objects.begin(); object_it != objects.end(); object_it++) {
		((Bomb *)((*object_it).get()))->checkTime();
		((Bomb *)((*object_it).get()))->updateTimer(objects[0].get());
		((Bomb *)((*object_it).get()))->updatePower((AObject *)my_wall2);
		std::cout << "Entering checkBreak wall1" << std::endl;
		my_wall1->checkBreak((*object_it).get());
		std::cout << "Entering checkBreak wall2" << std::endl;
		my_wall2->checkBreak((*object_it).get());
	}
	return 0;
}

void	test_character(Positions chara_pos, Positions bomb_pos, std::vector<int> sprites)
{
	ACharacter		*charac(new ACharacter(1, chara_pos));
	AObject			*bomb1(new Bomb(3, bomb_pos, sprites, sprites));
	std::vector<AObject *>	objects;

	objects.push_back(bomb1);
	while (1) {
		std::cout << "Charac pos : {" << chara_pos.x << ", " << chara_pos.y << "}" << std::endl;
		charac->moveUp(objects);
		chara_pos = charac->getPos();
	}
}

int	main()
{
	Positions	bomb_pos;
	Positions	wall_pos;
	Positions	chara_pos;
	Positions	side_wall_pos;
	std::vector<int>	sprites;

	//bomb_pos.x = 0;
	//bomb_pos.y = 3;
	wall_pos.x = 0;
	wall_pos.y = 1;
	side_wall_pos.x = 0;
	side_wall_pos.y = 2;
	wall_pos = wall_pos;
	side_wall_pos = side_wall_pos;

	chara_pos.x = 0;
	chara_pos.y = 5;
	bomb_pos.x = 0;
	bomb_pos.y = 0;
	sprites.clear();
	//drop_bomb(bomb_pos, wall_pos, side_wall_pos, sprites);
	test_character(chara_pos, bomb_pos, sprites);
=======
// main
// File description:
// main for gene map
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "include/ACharacter.hpp"
#include "include/action.hpp"
#include "include/Map.hpp"
#include "include/objects/classWall.hpp"
#include "include/objects/positions.hpp"
#include "include/IA.hpp"
#include "include/Player.hpp"

void	openFieldStartChara(Positions *coord)
{
	if ((coord->y == 0 && coord->x == 10) ||
	    (coord->y == 1 && coord->x == 12) ||
	    (coord->y == 8 && coord->x == 12)) {
		coord->y += 1;
		coord->x = 1;
	}
	if (coord->y == 9 && coord->x == 12) {
		coord->y += 1;
		coord->x = 3;
	}
	if (coord->y == 10 && coord->x == 11)
		coord->y = 11;
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

void	Map::generateMap()
{
	Positions			coord;
	int				rand;
	std::vector<int>		test;

	coord.x = 2;
	coord.y = 0;
	while (coord.y != 11) {
		rand = 101;
		openFieldStartChara(&coord);
		while (rand > 100) {
			rand = 1 + std::rand()/((100 + 1u)/6);
		}
		if (rand <= 90) {
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

void	Map::setSizeMap(int posX, int posY)
{
	this->_mapSize.x = posX;
	this->_mapSize.y = posY;
}

int	main()
{
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
>>>>>>> origin/Paul/generation_map
	return 0;
}
