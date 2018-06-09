#include "ACharacter.hpp"
#include "action.hpp"
#include "classBomb.hpp"
#include "classUnbrWall.hpp"
#include "enumObjectType.hpp"
#include "positions.hpp"
#include "checkDie.hpp"
#include "classBonus.hpp"
#include "classWall.hpp"
#include "getObjectAtPosition.hpp"
#include "Map.hpp"
#include "json.hpp"
#include <iostream>

int	main()
{
	// Variables pour test

	Map		map(10, 10);
	Map		loading(10, 10);
	AObject		*obj;
	ACharacter	*charac;
	Positions	characPos;
	Positions	objPos;
	
	// Definitions des positions des obj et des characs
	
	std::vector<int>	sprites;
	Positions		bombPos1;
	Positions		bombPos2;	
	Positions		bombPos3;
	Positions		bombPos4;
	Positions		wallPos1;
	Positions		wallPos2;
	Positions		wallPos3;
	Positions		wallPos4;
	Positions		bombUpPos;	
	Positions		speedUpPos;
	Positions		fireUpPos;
	Positions		wallPassPos;
	Positions		characPos1;
	Positions		characPos2;
	Positions		characPos3;
	Positions		characPos4;

	sprites.clear();
	bombPos1.x = 1;
	bombPos1.y = 21;
	bombPos2.x = 4;
	bombPos2.y = 12;
	bombPos3.x = 62;
	bombPos3.y = 7;
	bombPos4.x = 24;
	bombPos4.y = 31;
	wallPos1.x = 23;
	wallPos1.y = 5;
	wallPos2.x = 4;
	wallPos2.y = 13;
	wallPos3.x = 91;
	wallPos3.y = 63;
	wallPos4.x = 2;
	wallPos4.y = 13;
	characPos1.x = 42;
	characPos1.y = 49;
	characPos2.x = 12;
	characPos2.y = 65;
	characPos3.x = 15;
	characPos3.y = 2;
	characPos4.x = 32;
	characPos4.y = 6;
	bombUpPos.x = 23;
	bombUpPos.y = 72;
	speedUpPos.x = 21;
	speedUpPos.y = 89;
	fireUpPos.x = 12;
	fireUpPos.y = 15;
	wallPassPos.x = 97;
	wallPassPos.y = 62;

	// Création des objets et des characs

	std::unique_ptr<AObject>	bomb1(new Bomb(3, bombPos1, sprites, sprites));
	std::unique_ptr<AObject>	bomb2(new Bomb(3, bombPos2, sprites, sprites));
	std::unique_ptr<AObject>	bomb3(new Bomb(3, bombPos3, sprites, sprites));
	std::unique_ptr<AObject>	bomb4(new Bomb(3, bombPos4, sprites, sprites));
	std::unique_ptr<AObject>	wall1(new Wall(wallPos1, sprites, sprites));	
	std::unique_ptr<AObject>	wall2(new Wall(wallPos2, sprites, sprites));
	std::unique_ptr<AObject>	wall3(new Wall(wallPos3, sprites, sprites));
	std::unique_ptr<AObject>	wall4(new Wall(wallPos4, sprites, sprites));
	std::unique_ptr<AObject>	bombUp(new bonusBombUp(bombUpPos, sprites));
	std::unique_ptr<AObject>	speedUp(new bonusSpeedUp(speedUpPos, sprites));
	std::unique_ptr<AObject>	wallPass(new bonusWallPass(wallPassPos, sprites));
	std::unique_ptr<AObject>	fireUp(new bonusFireUp(fireUpPos, sprites));
	std::unique_ptr<ACharacter>	charac1(new ACharacter(1, characPos1));
	std::unique_ptr<ACharacter>	charac2(new ACharacter(2, characPos2));
	std::unique_ptr<ACharacter>	charac3(new ACharacter(3, characPos3));
	std::unique_ptr<ACharacter>	charac4(new ACharacter(4, characPos4));

	map.addMapElem(std::move(bomb1));
	map.addMapElem(std::move(bomb2));
	map.addMapElem(std::move(bomb3));
	map.addMapElem(std::move(bomb4));
	map.addMapElem(std::move(wall1));
	map.addMapElem(std::move(wall2));
	map.addMapElem(std::move(wall3));
	map.addMapElem(std::move(wall4));
	map.addMapElem(std::move(bombUp));
	map.addMapElem(std::move(wallPass));
	map.addMapElem(std::move(speedUp));
	map.addMapElem(std::move(fireUp));
	map.addCharacter(std::move(charac1));
	map.addCharacter(std::move(charac2));
	map.addCharacter(std::move(charac3));
	map.addCharacter(std::move(charac4));

	// Test of save and load
	
	std::cout << "Before save:" << std::endl;
	for (int it = 0; it < map.getNbMapElem(); it++) {
		obj = map.getMapElem(it);
		objPos = obj->getPos();
		std::cout << "objType = " << obj->getObjectType()
			  << ", pos x = " << objPos.x << " et pos y = " << objPos.y
			  << ", destroyed = " << obj->getIsDestroyed() << std::endl;
	}
	for (int it = 0; it < map.getNbCharacter(); it++) {
		charac = map.getCharacter(it);
		characPos = charac->getPos();
		std::cout << "nbrPlayer = " << charac->getPlayerNbr()
			  << ", pos x = " << characPos.x << " et pos y = " << characPos.y
			  << ", isDead = " << charac->getIsDead() << std::endl;
	}	
	
	map.saveMap();

	std::cout << "After save:" << std::endl;
	for (int it = 0; it < map.getNbMapElem(); it++) {
		obj = map.getMapElem(it);
		objPos = obj->getPos();
		std::cout << "objType = " << obj->getObjectType()
			  << ", pos x = " << objPos.x << " et pos y = " << objPos.y
			  << ", destroyed = " << obj->getIsDestroyed() << std::endl;
	}
	for (int it = 0; it < map.getNbCharacter(); it++) {
		charac = map.getCharacter(it);
		characPos = charac->getPos();
		std::cout << "nbrPlayer = " << charac->getPlayerNbr()
			  << ", pos x = " << characPos.x << " et pos y = " << characPos.y
			  << ", isDead = " << charac->getIsDead() << std::endl;
	}	

	loading.loadMapFromSave("save.json");
	
	std::cout << "After loading:" << std::endl;
	for (int it = 0; it < loading.getNbMapElem(); it++) {
		obj = loading.getMapElem(it);
		objPos = obj->getPos();
		std::cout << "objType = " << obj->getObjectType()
			  << ", pos x = " << objPos.x << " et pos y = " << objPos.y
			  << ", destroyed = " << obj->getIsDestroyed() << std::endl;
	}
	for (int it = 0; it < map.getNbCharacter(); it++) {
		charac = map.getCharacter(it);
		characPos = charac->getPos();
		std::cout << "nbrPlayer = " << charac->getPlayerNbr()
			<< ", pos x = " << characPos.x << " et pos y = " << characPos.y
			<< ", isDead = " << charac->getIsDead() << std::endl;
	}
	return 0;
}
