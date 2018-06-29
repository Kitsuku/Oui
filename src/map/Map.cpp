/*
** EPITECH PROJECT, 2018
** Map functions
** File description:
**
*/

#include "Player.hpp"
#include "Map.hpp"
#include "Character.hpp"
#include "Action.hpp"
#include "Bomb.hpp"
#include "UnbrWall.hpp"
#include "enumObjectType.hpp"
#include "Positions.hpp"
#include "IA.hpp"
#include "Bonus.hpp"
#include "Wall.hpp"
#include "Object.hpp"
#include "json.hpp"
#include <string>
#include <iostream>
#include <fstream>

Map::Map(int x, int y, const std::string &path): _path(path)
{
	_mapSize.x = 13;
	_mapSize.y = 11;
}

Positions	Map::getMapSize()
{
	return _mapSize;
}

AObject		*Map::getMapElem(unsigned int nb)
{
	if (nb < _map.size())
		return _map.at(nb).get();
	return nullptr;
}

ACharacter	*Map::getCharacter(unsigned int nb)
{
	if (nb < _characters.size())
		return _characters.at(nb).get();
	return nullptr;
}

int		Map::getNbMapElem()
{
	return _map.size();
}

int		Map::getNbCharacter()
{
	return _characters.size();
}

void		Map::addMapElem(std::unique_ptr<AObject> obj)
{
	_map.push_back(std::move(obj));
}

void		Map::addCharacter(std::unique_ptr<ACharacter> charac)
{
	_characters.push_back(std::move(charac));
}

std::string	Map::getBackground()
{
	return _backGround;
}

std::string	Map::getGround()
{
	return _ground;
}

const std::string	&Map::getPath() const
{
	return _path;
}

void    Map::openFieldStartChara(Positions *coord)
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

int	Map::getNbCharacterAlive()
{
	int	nb = 0;
	int	lenVector = 0;

	for (auto it = _characters.begin(); it != _characters.end(); it++) {
		if ((_characters[lenVector].get()->getNbrPlayer()) > 0)
		    nb += 1;
		lenVector += 1;
	}
	return nb;
}

int	Map::getNbIAAlive()
{
	int	nb = 0;
	int	lenVector = 0;

	for (auto it = _characters.begin(); it != _characters.end(); it++) {
		if ((_characters[lenVector].get()->getNbrPlayer()) < 0)
			nb += 1;
		lenVector += 1;
	}
	return nb;
}

std::vector<Positions>	Map::coordForUnbrWall()
{
	Positions		pos;
	std::vector<Positions>	ret;
	std::string		finishWall = "res/rockwall_height.bmp";

	for (int y = 1; y < 10; y += 2) {
		for(int x = 1; x < 12; x += 2) {
			pos.y = y;
			pos.x = x;
			ret.push_back(pos);
			std::unique_ptr<AObject>        newWall = std::make_unique<UnbrWall>(pos, finishWall);
			this->_map.push_back(std::move(newWall));
		}
	}
	return ret;
}

bool	Map::isUnbrWall(std::vector<Positions> posUnbrWall, Positions coord)
{
	int	temp = 0;

	for (std::vector<Positions>::iterator it = posUnbrWall.begin(); it != posUnbrWall.end(); it++) {
		if (posUnbrWall.at(temp).x == coord.x && posUnbrWall.at(temp).y == coord.y)
			return false;
		temp += 1;
	}
	return true;
}

void    Map::generateMap()
{
	Positions		coord;
	int			rand;
	std::vector<Positions>	posUnbrWall = this->coordForUnbrWall();
	std::string		wall = "res/wall.jpg";
	std::string		unWall = "res/brokenWall.png";
	std::string		finishWall = "res/rockwall_height.bmp";

	coord.x = 2;
	coord.y = 0;
	while (coord.y != 11) {
		openFieldStartChara(&coord);
		rand = (1 + std::rand()/((100 + 1u)/6)) % 100;
		if (coord.x <= 12 && coord.y <= 10 && isUnbrWall(posUnbrWall, coord) && rand <= 83) {
			std::unique_ptr<AObject>        newWall = std::make_unique<Wall>(coord, wall, unWall);
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
	this->_mapSize.x = 13;
	this->_mapSize.y = 11;
}

void	Map::generateCharacter(int nbPlayer)
{
	Positions	pos;
	std::vector<std::string>	vec_sprite = {"res/sydney.md2", "res/sydney.bmp"};
	std::string	living = "res/Dynamite/dinamite.obj";
	std::string	dead = "res/fire.bmp";

	if (nbPlayer == 1) {
		pos.x = 0;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newChara = std::make_unique<Player>(1, pos, vec_sprite, living, dead);
		this->_characters.push_back(std::move(newChara));
		pos.x = _mapSize.x - 1;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newIA1 = std::make_unique<IA>(-1, pos, vec_sprite, living, dead);
		this->_characters.push_back(std::move(newIA1));
		pos.x = 0;
		pos.y = _mapSize.y - 1;
		std::unique_ptr<ACharacter>     newIA2 = std::make_unique<IA>(-2, pos, vec_sprite, living, dead);
		this->_characters.push_back(std::move(newIA2));
		pos.x = _mapSize.x - 1;
		pos.y = _mapSize.y - 1;
		std::unique_ptr<ACharacter>     newIA3 = std::make_unique<IA>(-3, pos, vec_sprite, living, dead);
		this->_characters.push_back(std::move(newIA3));
	}
	else if (nbPlayer == 2){
		pos.x = 0;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newChara = std::make_unique<Player>(1, pos, vec_sprite, living, dead);
		this->_characters.push_back(std::move(newChara));
		pos.x = _mapSize.x - 1;
		pos.y = 0;
		std::unique_ptr<ACharacter>     newChara2 = std::make_unique<Player>(2, pos, vec_sprite, living, dead);
		this->_characters.push_back(std::move(newChara2));
		pos.x = 0;
		pos.y = _mapSize.y - 1;
		std::unique_ptr<ACharacter>     newIA = std::make_unique<IA>(-1, pos, vec_sprite, living, dead);
		this->_characters.push_back(std::move(newIA));
		pos.x = _mapSize.x - 1;
		pos.y = _mapSize.y - 1;
		std::unique_ptr<ACharacter>     newIA2 = std::make_unique<IA>(-2, pos, vec_sprite, living, dead);
		this->_characters.push_back(std::move(newIA2));
	}
}

void	Map::saveObj(AObject *obj, std::string fileName)
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

void	Map::saveBomb(AObject *obj, std::string fileName)
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

void	Map::saveCharacter(ACharacter *character, std::string fileName)
{
	std::ofstream	file;
	Positions	characPos;
	nlohmann::json	j;

	file.open(fileName, std::ios::ate | std::ios::app);
	characPos = character->getPos();
	j["type"] = "Character";
	j["playerNbr"] = character->getNbrPlayer();
	j["maxBombNbr"] = character->getNbrMaxBomb();
	j["putBombNbr"] = character->getNbrPutBomb();
	j["fireRange"] = character->getFireRange();
	j["speed"] = character->getSpeed();
	j["wallPass"] = character->getWallPass();
	j["posX"] = characPos.x;
	j["posY"] = characPos.y;
	j["isDead"] = character->getIsDead();
	j["sprites"] = character->getSprites();
	j["action"] = character->getAction();
	j["oldDir"] = character->getOldDir();
	j["oldAction"] = character->getOldAction();
	j["bombLiveSprite"] = character->getBombLiveSprite();
	j["bombDeathSprite"] = character->getBombDeathSprite();
	j["delayDead"] = character->getDelayDead();
	file << j << std::endl;
	file.close();
}

void	Map::saveMap(std::string save)
{
	AObject		*obj;
	ACharacter	*character;
	std::ofstream	file;

	file.open(save, std::ofstream::out | std::ofstream::trunc);
	file.close();
	for (int it = 0; it != getNbMapElem(); it++) {
		obj = getMapElem(it);
		if (obj->getObjectType() == BOMB)
			saveBomb(obj, save);
		else
			saveObj(obj,save);
	}
	for (int it = 0; it < getNbCharacter(); it++) {
		character = getCharacter(it);
		saveCharacter(character, save);
	}
}

std::unique_ptr<AObject>	Map::loadBomb(nlohmann::json j)
{
	std::unique_ptr<Bomb>	bomb = std::make_unique<Bomb>();
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

std::unique_ptr<AObject>	Map::loadObj(nlohmann::json j)
{
	std::unique_ptr<AObject>	obj = std::make_unique<Object>();
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

std::unique_ptr<ACharacter>	Map::loadCharacter(nlohmann::json j)
{
	std::unique_ptr<ACharacter>	character = std::make_unique<Player>();
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
	character->setOldDir(j["oldDir"]);
	character->setOldAction(j["oldAction"]);
	character->setBombLiveSprite(j["bombLiveSprite"]);
	character->setBombDeathSprite(j["bombDeathSprite"]);
	character->setDelayDead(j["delayDead"]);
	return (std::move(character));
}

void	Map::loadMapFromSave(std::string fileName)
{
	std::ifstream	file(_path + "save/" + fileName);
	nlohmann::json	j;

	setSpriteGroundAndBackGround();
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

void	Map::setSpriteGroundAndBackGround()
{
	std::ifstream	file((_path + ".conf").c_str(), std::ios::in);
	std::string	buffer;

	if (file) {
		getline(file, buffer);
		std::cout << buffer << std::endl;
		this->_backGround = buffer;
		getline(file, buffer);
		std::cout << buffer << std::endl;
		this->_ground = buffer;
		file.close();
	} else
		std::cerr << "Error with configuration." << std::endl;
}
