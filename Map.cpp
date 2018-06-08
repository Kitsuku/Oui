//
// EPITECH PROJECT, 2018
// Map functions
// File description:
// 
//

#include "include/Player.hpp"
#include "include/Map.hpp"
#include "include/ACharacter.hpp"
#include "include/action.hpp"
#include "include/objects/classBomb.hpp"
#include "include/objects/classUnbrWall.hpp"
#include "include/objects/enumObjectType.hpp"
#include "include/objects/positions.hpp"
#include "include/objects/checkDie.hpp"
#include "include/objects/classBonus.hpp"
#include "include/objects/classWall.hpp"
#include "include/objects/getObjectAtPosition.hpp"
#include "include/objects/Object.hpp"
#include "json-develop/single_include/nlohmann/json.hpp"
#include <string>
#include <iostream>
#include <fstream>

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
	j["playerNbr"] = character->getPlayerNbr();
	j["bombNbr"] = character->getBombNbr();
	j["fireRange"] = character->getFireRange();
	j["speed"] = character->getSpeed();
	j["wallPass"] = character->getWallPass();
	j["posX"] = characPos.x;
	j["posY"] = characPos.y;
	j["isDead"] = character->getIsDead();
	j["leftSprites"] = character->getSprites("left");
	j["rightSprites"] = character->getSprites("right");
	j["upSprites"] = character->getSprites("up");
	j["downSprites"] = character->getSprites("down");
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
	bomb->setDefaultPower(j["defaultPower"]);
	bomb->setUpPower(j["upPower"]);
	bomb->setDownPower(j["downPower"]);
	bomb->setLeftPower(j["leftPower"]);
	bomb->setRightPower(j["rightPower"]);
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
	character->setNbrBomb(j["bombNbr"]);
	character->setFireRange(j["fireRange"]);
	character->setSpeed(j["speed"]);
	character->setWallPass(j["wallPass"]);
	character->setIsDead(j["isDead"]);
	character->setLeftSprites(j["leftSprites"]);
	character->setRightSprites(j["rightSprites"]);
	character->setUpSprites(j["upSprites"]);
	character->setDownSprites(j["downSprites"]);
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

