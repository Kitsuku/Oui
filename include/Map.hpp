//
// EPITECH PROJECT, 2018
// Map object
// File description:
//
//

#ifndef MAP_HPP_
# define MAP_HPP_

#include "objects/Positions.hpp"
#include "ACharacter.hpp"
#include "Bomb.hpp"
#include "Wall.hpp"
#include "objects/AObject.hpp"
#include "Graphics.hpp"
#include <vector>
#include <memory>

class	Map
{
public:
	Map(int x, int y) { _mapSize.x = 13; _mapSize.y = 11; }
	~Map() {}
	void	setSizeMap(int, int);
	void	generateCharacter(int);
	void	generateMap();
	void	loadMapFromSave(std::string);
	void	saveMap(std::string);
	std::vector<AObject *>	getAllObjects();
	std::vector<ACharacter *>	getAllCharacters();
	Positions	getMapSize() { return _mapSize; }
	AObject	*getMapElem(unsigned int nb) {
		if (nb < _map.size())
			return _map.at(nb).get();
		return nullptr;
	}
	ACharacter	*getCharacter(unsigned int nb) {
		if (nb < _characters.size())
			return _characters.at(nb).get();
		return nullptr;
	}
	std::vector<Positions>	coordForUnbrWall();
	int	getNbMapElem() { return _map.size(); }
	int	getNbCharacter() { return _characters.size(); }
	int	getNbCharacterAlive();
	void	addMapElem(std::unique_ptr<AObject> obj) { _map.push_back(std::move(obj)); }
	void	addCharacter(std::unique_ptr<ACharacter> charac) { _characters.push_back(std::move(charac)); }
	void	play(Graphics *);
	void	playObjects();
	void	checkBreakWalls(Wall *);
	void	playWalls();
	void	playBombs();
	void	removeNbrBombCharacter(AObject *);
	void	checkDeleteObjects();
	void	checkDeleteCharac();
	void	addNewElem(AObject *object);
	void	giveActionToCharac(const std::vector<irr::SEvent::SJoystickEvent> &joystickData);
	void	startPause(Graphics *);
	unsigned int	countCharacters();
	void	updateBombTimer(Bomb *, unsigned int);
	AObject	*updateBombPower(AObject *);
	void	setSpriteGroundAndBackGround();
	void	AddBonus(AObject *);
	std::string getBackground();
	std::string getGround();
	int getNbIAAlive();

protected:
	std::vector<std::unique_ptr<AObject>>		_map;
	std::vector<std::unique_ptr<ACharacter>>	_characters;
	Positions					_mapSize;
	std::string					_ground;
	std::string					_backGround;
};

#endif /* !MAP_HPP_ */
