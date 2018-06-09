//
// EPITECH PROJECT, 2018
// Map functions
// File description:
//
//

#include "Player.hpp"
#include "Map.hpp"
#include "Character.hpp"
#include "Action.hpp"
#include "Bomb.hpp"
#include "UnbrWall.hpp"
#include "enumObjectType.hpp"
#include "Positions.hpp"
#include "IA.hpp"
#include "checkDie.hpp"
#include "Bonus.hpp"
#include "Wall.hpp"
#include "getObjectAtPosition.hpp"
#include "Object.hpp"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>

void    openFieldStartChara(Positions *coord)
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

std::vector<AObject *>	Map::getAllObjects()
{
	std::vector<AObject *>	allObjects;

	for (int it = 0; it != getNbMapElem(); it++) {
		allObjects.push_back(getMapElem(it));
	}
	return allObjects;
}

std::vector<ACharacter *>	Map::getAllCharacters()
{
	std::vector<ACharacter *>	allCharacters;

	for (int it = 0; it != getNbCharacter(); it++)
		allCharacters.push_back(getCharacter(it));
	return allCharacters;
}

void    Map::generateMap()
{
	Positions		coord;
	int			rand;
	std::string	test;

	coord.x = 2;
	coord.y = 0;
	while (coord.y != 11) {
		rand = 101;
		openFieldStartChara(&coord);
		while (rand > 100) {
			rand = 1 + std::rand()/((100 + 1u)/6);
		}
		if (rand <= 90) {
			std::unique_ptr<AObject>        newWall(new Wall(coord, test, test));
			this->_map.push_back(std::move(newWall));
		}
		coord.x += 1;
		if (static_cast<int> (coord.x) % 13 == 0) {
			coord.x = 0;
			coord.y += 1;
		}
	}
}

void	Map::setSizeMap(float posX, float posY)
{
	this->_mapSize.x = posX;
	this->_mapSize.y = posY;
}

void	Map::generateCharacter(int nbPlayer)
{
	Positions	pos;
	std::vector<std::string>	vec_sprite;
	std::string	sprite;

	if (nbPlayer == 1) {
		pos.x = 0;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newChara(new Player(1, pos, vec_sprite, sprite, sprite));
		this->_characters.push_back(std::move(newChara));
		pos.x = 12;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newIA1(new IA(-1, pos, vec_sprite, sprite, sprite));
		this->_characters.push_back(std::move(newIA1));
		pos.x = 0;
		pos.y = 10;
		std::unique_ptr<ACharacter>     newIA2(new IA(-2, pos, vec_sprite, sprite, sprite));
		this->_characters.push_back(std::move(newIA2));
		pos.x = 12;
		pos.y = 10;
		std::unique_ptr<ACharacter>     newIA3(new IA(-3, pos, vec_sprite, sprite, sprite));
		this->_characters.push_back(std::move(newIA3));
	}
	else if (nbPlayer == 2){
		pos.x = 0;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newChara(new Player(1, pos, vec_sprite, sprite, sprite));
		this->_characters.push_back(std::move(newChara));
		pos.x = 12;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newChara2(new Player(2, pos, vec_sprite, sprite, sprite));
		this->_characters.push_back(std::move(newChara2));
		pos.x = 0;
		pos.y = 10;
		std::unique_ptr<ACharacter>     newIA(new IA(-1, pos, vec_sprite, sprite, sprite));
		this->_characters.push_back(std::move(newIA));
		pos.x = 12;
		pos.y = 10;
		std::unique_ptr<ACharacter>     newIA2(new IA(-2, pos, vec_sprite, sprite, sprite));
		this->_characters.push_back(std::move(newIA2));
	}
}

void	saveObj(AObject *obj, std::string fileName)
{
	std::ofstream	file;
	Positions	objPos = obj->getPos();
	nlohmann::json	j;

	file.open(fileName, std::ios::ate | std::ios::app);
	j["type"] = "Object";
	j["objType"] = obj->getObjectType();
	j["livingSprite"] = obj->getLivingSprites();
	j["dyingSprite"] = obj->getDyingSprites();
	j["posX"] = objPos.x;
	j["posY"] = objPos.y;
	j["isDestroyed"] = obj->getIsDestroyed();
	file << j << std::endl;
	file.close();
}

void	saveBomb(AObject *obj, std::string fileName)
{
	std::ofstream	file;
	Bomb		*bomb = static_cast<Bomb *> (obj);
	Positions	bombPos = bomb->getPos();
	nlohmann::json	j;

	file.open(fileName, std::ios::ate | std::ios::app);
	j["type"] = "Object";
	j["objType"] = BOMB;
	j["livingSprite"] = bomb->getLivingSprites();
	j["dyingSprite"] = bomb->getDyingSprites();
	j["posX"] = bombPos.x;
	j["posY"] = bombPos.y;
	j["isDestroyed"] = bomb->getIsDestroyed();
	j["defaultPower"] = bomb->getPower("default");
	j["upPower"] = bomb->getPower("up");
	j["downPower"]= bomb->getPower("down");
	j["leftPower"] = bomb->getPower("left");
	j["rightPower"] = bomb->getPower("right");
	j["bombTime"] = bomb->getTime();
	file << j << std::endl;
	file.close();
}

void	saveCharacter(ACharacter *character, std::string fileName)
{
	std::ofstream	file;
	Positions	characPos;
	nlohmann::json	j;

	file.open(fileName, std::ios::ate | std::ios::app);
	characPos = character->getPos();
	j["type"] = "Character";
	j["playerNbr"] = character->getNbrPlayer();
	j["maxBombNbr"] = character->getNbrMaxBomb();
	j["putbBmbNbr"] = character->getNbrPutBomb();
	j["fireRange"] = character->getFireRange();
	j["speed"] = character->getSpeed();
	j["wallPass"] = character->getWallPass();
	j["posX"] = characPos.x;
	j["posY"] = characPos.y;
	j["isDead"] = character->getIsDead();
	j["sprites"] = character->getSprites();
	j["action"] = character->getAction();
	file << j << std::endl;
	file.close();
}

void	Map::saveMap()
{
	AObject		*obj;
	ACharacter	*character;
	std::ofstream	file;

	file.open("save.json", std::ofstream::out | std::ofstream::trunc);
	file.close();
	for (int it = 0; it != getNbMapElem(); it++) {
		obj = getMapElem(it);
		if (obj->getObjectType() == BOMB)
			saveBomb(obj, "save.json");
		else
			saveObj(obj,"save.json");
	}
	for (int it = 0; it < getNbCharacter(); it++) {
		character = getCharacter(it);
		saveCharacter(character, "save.json");
	}
}

std::unique_ptr<AObject>	loadBomb(nlohmann::json j)
{
	std::unique_ptr<Bomb>	bomb(new Bomb());
	Positions			bombPos;

	bombPos.x = j["posX"];
	bombPos.y = j["posY"];
	bomb->setObjectType(BOMB);
	bomb->setLivingSprites(j["livingSprite"]);
	bomb->setDyingSprites(j["dyingSprite"]);
	bomb->setIsDestroyed(j["isDestroyed"]);
	bomb->setPos(bombPos);
	bomb->setTime(j["bombTime"]);
	bomb->setPower("default", j["defaultPower"]);
	bomb->setPower("up", j["upPower"]);
	bomb->setPower("down", j["downPower"]);
	bomb->setPower("left", j["leftPower"]);
	bomb->setPower("right", j["rightPower"]);
	return (std::move(bomb));
}

std::unique_ptr<AObject>	loadObj(nlohmann::json j)
{
	std::unique_ptr<AObject>	obj(new Object());
	Positions			objPos;

	objPos.x = j["posX"];
	objPos.y = j["posY"];
	obj->setObjectType(j["objType"]);
	obj->setLivingSprites(j["livingSprite"]);
	obj->setDyingSprites(j["dyingSprite"]);
	obj->setIsDestroyed(j["isDestroyed"]);
	obj->setPos(objPos);
	return (std::move(obj));
}

std::unique_ptr<ACharacter>	loadCharacter(nlohmann::json j)
{
	std::unique_ptr<ACharacter>	character(new Player());
	Positions			characPos;

	characPos.x = j["posX"];
	characPos.y = j["posY"];
	character->setPos(characPos);
	character->setNbrPlayer(j["playerNbr"]);
	character->setNbrMaxBomb(j["maxBombNbr"]);
	character->setNbrPutBomb(j["putBombNbr"]);
	character->setFireRange(j["fireRange"]);
	character->setSpeed(j["speed"]);
	character->setWallPass(j["wallPass"]);
	character->setIsDead(j["isDead"]);
	character->setSprites(j["sprites"]);
	character->setAction(j["action"]);
	return (std::move(character));
}

void	Map::loadMapFromSave(std::string fileName)
{
	std::ifstream	file(fileName);
	nlohmann::json	j;

	while (file) {
		try {
			file >> j;
			if (j["type"] == "Object") {
				if (j["objType"] == BOMB)
					this->addMapElem(std::move(loadBomb(j)));
				else
					this->addMapElem(std::move(loadObj(j)));
			}
			else
				this->addCharacter(std::move(loadCharacter(j)));
		}
		catch (nlohmann::detail::parse_error &e) {
			file.close();
		}
	}
}
